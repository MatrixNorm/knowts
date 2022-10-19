# grep

### искать только в файлах текущей директории, без рекурсии
```bash
grep * .* -e 'cargo' -d skip --exclude=.zsh_history
```
`-d skip` - пропустить директории
`* .*` - все нескрытые и скрытые

### рекурсивно
```bash
grep -rl . -e 'cargo' --exclude=.zsh_history --exclude-dir={.cache,.local}
```
