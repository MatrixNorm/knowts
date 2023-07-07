### github fork repo

### Delete file from history and remote repo

XXX a.out

### Add to .gitignore file already in version control

### GIT_SSH_COMMAND environment variable

to show verbose messages while doing `git pull`

```
> GIT_SSH_COMMAND="ssh -vvv" git push
```

### Rename a Git branch locally and remotely

the feature move exists to rename the branch locally

```
git branch --move <old_name> <new_name>
```

but to push it, you must delete the old and push the new

```
git checkout <new_name>
git push origin [--set-upstream] <new_name>
git push origin --delete <old_name>
```

`--set-upstream` is optional, it configure the new local branch to track the pushed one