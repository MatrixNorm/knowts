```C
fd_set rfds;
struct timeval tv;
int retval;

FD_ZERO(&rfds);
FD_SET(0, &rfds);

tv.tv_sec = 5;
tv.tv_usec = 0;

retval = select(1, &rfds, NULL, NULL, &tv);
```

```C
#define __FDS_BITS(set) ((set)->__fds_bits)

#define __FD_ZERO(s) \
  do {									                                \
    unsigned int __i;							                        \
    fd_set *__arr = (s);						                        \
    for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i)    \
      __FDS_BITS (__arr)[__i] = 0;					                    \
  } while (0)

#define __FD_SET(d, s) \
  ((void) (__FDS_BITS (s)[__FD_ELT(d)] |= __FD_MASK(d)))
```

```C
// FD_ZERO(&rfds);

do {					      
    unsigned int __i;					      
    fd_set *__arr = (&rfds);
    for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i)
      ((__arr) -> __fds_bits)[__i] = 0;
  } while (0)


#define	__FD_ELT(d)	((d) / __NFDBITS)
#define	__FD_MASK(d)	((__fd_mask) (1UL << ((d) % __NFDBITS)))

// FD_SET(k, &rfds);

((void) (__FDS_BITS (&rfds)[__FD_ELT(k)] |= __FD_MASK(k)))

((void) (((&rfds) -> __fds_bits)[ ((k) / __NFDBITS) ] |= __FD_MASK(k)))

((void) ( ((&rfds) -> __fds_bits) [(k / 64)] |= __FD_MASK(k) ))

((void) ( ((&rfds) -> __fds_bits) [(k / 64)] |= ((__fd_mask) (1UL << (k % 64))) ))
// 1UL = 0...(63 zeros)...01
// 1UL << (k % 64) = 0...010...0 (1 на k-ом месте)
```

```C
// /fs/select.c

int core_sys_select(int n, fd_set __user *inp, fd_set __user *outp,
			   fd_set __user *exp, struct timespec64 *end_time)
{
	fd_set_bits fds;
	void *bits;
	int ret, max_fds;
	size_t size, alloc_size;
	struct fdtable *fdt;
	/* Allocate small arguments on the stack to save memory and be faster */
	long stack_fds[ SELECT_STACK_ALLOC / sizeof(long) ];
  // 256 / 8

	ret = -EINVAL;
	if (n < 0)
		goto out_nofds;

	/* max_fds can increase, so grab it once to avoid race */
	rcu_read_lock();

  /* The current pointer (of type struct task_struct) refers to the user process currently executing.
     During the execution of a system call, such as open or read, the current process is the
     one that invoked the call.

    struct task_struct {
      ...
      // Open file information: open file table structure
      struct files_struct		*files;
    }

    struct files_struct {
      ...
      struct fdtable __rcu *fdt;
      spinlock_t file_lock ____cacheline_aligned_in_smp;
    }

    struct fdtable {
      unsigned int max_fds;
      struct file __rcu **fd;      
      unsigned long *close_on_exec;
      unsigned long *open_fds;
      unsigned long *full_fds_bits;
      struct rcu_head rcu;
    }
  */
	fdt = files_fdtable(current->files);
  /*
  #define files_fdtable(files) \
	  rcu_dereference_check_fdtable((files), (files)->fdt)

  fdt = files_fdtable(current->files);
  ==>>>
  rcu_dereference_check_fdtable(
    (current->files),
    (current->files)->fdt
  )
  ==>>>
  rcu_dereference_check(
    (current->files)->fdt,
    lockdep_is_held(&(current->files)->file_lock)
  )
  ==>>>
  XXX
  */
	max_fds = fdt->max_fds;
	rcu_read_unlock();
  
	if (n > max_fds)
		n = max_fds;

	/*
	 * We need 6 bitmaps (in/out/ex for both incoming and outgoing),
	 * since we used fdset we need to allocate memory in units of
	 * long-words. 
	 */
  /*
    // How many longwords for "nr" bits?
    #define FDS_BITPERLONG	(8*sizeof(long))
    #define FDS_LONGS(nr)	(((nr)+FDS_BITPERLONG-1)/FDS_BITPERLONG)
    #define FDS_BYTES(nr)	(FDS_LONGS(nr)*sizeof(long))
  */
	size = FDS_BYTES(n);
  // ???
	bits = stack_fds;
	if (size > sizeof(stack_fds) / 6) {
		/* Not enough space in on-stack array; must use kmalloc */
		ret = -ENOMEM;
		if (size > (SIZE_MAX / 6))
			goto out_nofds;

		alloc_size = 6 * size;
		bits = kvmalloc(alloc_size, GFP_KERNEL);
		if (!bits)
			goto out_nofds;
	}
	fds.in      = bits;
	fds.out     = bits +   size;
	fds.ex      = bits + 2*size;
	fds.res_in  = bits + 3*size;
	fds.res_out = bits + 4*size;
	fds.res_ex  = bits + 5*size;

	if ((ret = get_fd_set(n, inp, fds.in)) ||
	    (ret = get_fd_set(n, outp, fds.out)) ||
	    (ret = get_fd_set(n, exp, fds.ex)))
		goto out;
	zero_fd_set(n, fds.res_in);
	zero_fd_set(n, fds.res_out);
	zero_fd_set(n, fds.res_ex);

	ret = do_select(n, &fds, end_time);

	if (ret < 0)
		goto out;
	if (!ret) {
		ret = -ERESTARTNOHAND;
		if (signal_pending(current))
			goto out;
		ret = 0;
	}

	if (set_fd_set(n, inp, fds.res_in) ||
	    set_fd_set(n, outp, fds.res_out) ||
	    set_fd_set(n, exp, fds.res_ex))
		ret = -EFAULT;

out:
	if (bits != stack_fds)
		kvfree(bits);
out_nofds:
	return ret;
}
```


```C

static int do_select(int n, fd_set_bits *fds, struct timespec64 *end_time)
{
	ktime_t expire, *to = NULL;
	struct poll_wqueues table;
	poll_table *wait;
	int retval, i, timed_out = 0;
	u64 slack = 0;
	__poll_t busy_flag = net_busy_loop_on() ? POLL_BUSY_LOOP : 0;
	unsigned long busy_start = 0;

	rcu_read_lock();
	retval = max_select_fd(n, fds);
	rcu_read_unlock();

	if (retval < 0)
		return retval;
	n = retval;

	poll_initwait(&table);
	wait = &table.pt;
	if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
		wait->_qproc = NULL;
		timed_out = 1;
	}

	if (end_time && !timed_out)
		slack = select_estimate_accuracy(end_time);

	retval = 0;
	for (;;) {
		unsigned long *rinp, *routp, *rexp, *inp, *outp, *exp;
		bool can_busy_loop = false;

		inp = fds->in; outp = fds->out; exp = fds->ex;
		rinp = fds->res_in; routp = fds->res_out; rexp = fds->res_ex;

		for (i = 0; i < n; ++rinp, ++routp, ++rexp) {
			unsigned long in, out, ex, all_bits, bit = 1, j;
			unsigned long res_in = 0, res_out = 0, res_ex = 0;
			__poll_t mask;

			in = *inp++; out = *outp++; ex = *exp++;
			all_bits = in | out | ex;
			if (all_bits == 0) {
				i += BITS_PER_LONG;
				continue;
			}

			for (j = 0; j < BITS_PER_LONG; ++j, ++i, bit <<= 1) {
				struct fd f;
				if (i >= n)
					break;
				if (!(bit & all_bits))
					continue;
				mask = EPOLLNVAL;
				f = fdget(i);
				if (f.file) {
					wait_key_set(wait, in, out, bit,
						     busy_flag);
					mask = vfs_poll(f.file, wait);

					fdput(f);
				}
				if ((mask & POLLIN_SET) && (in & bit)) {
					res_in |= bit;
					retval++;
					wait->_qproc = NULL;
				}
				if ((mask & POLLOUT_SET) && (out & bit)) {
					res_out |= bit;
					retval++;
					wait->_qproc = NULL;
				}
				if ((mask & POLLEX_SET) && (ex & bit)) {
					res_ex |= bit;
					retval++;
					wait->_qproc = NULL;
				}
				/* got something, stop busy polling */
				if (retval) {
					can_busy_loop = false;
					busy_flag = 0;

				/*
				 * only remember a returned
				 * POLL_BUSY_LOOP if we asked for it
				 */
				} else if (busy_flag & mask)
					can_busy_loop = true;

			}
			if (res_in)
				*rinp = res_in;
			if (res_out)
				*routp = res_out;
			if (res_ex)
				*rexp = res_ex;
			cond_resched();
		}
		wait->_qproc = NULL;
		if (retval || timed_out || signal_pending(current))
			break;
		if (table.error) {
			retval = table.error;
			break;
		}

		/* only if found POLL_BUSY_LOOP sockets && not out of time */
		if (can_busy_loop && !need_resched()) {
			if (!busy_start) {
				busy_start = busy_loop_current_time();
				continue;
			}
			if (!busy_loop_timeout(busy_start))
				continue;
		}
		busy_flag = 0;

		/*
		 * If this is the first loop and we have a timeout
		 * given, then we convert to ktime_t and set the to
		 * pointer to the expiry value.
		 */
		if (end_time && !to) {
			expire = timespec64_to_ktime(*end_time);
			to = &expire;
		}

		if (!poll_schedule_timeout(&table, TASK_INTERRUPTIBLE,
					   to, slack))
			timed_out = 1;
	}

	poll_freewait(&table);

	return retval;
}
```