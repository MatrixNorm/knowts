
**ПРОБЛЕМА: спам контейнеров** ??? вроде и нет ничего
==============================

При работе с проектом происходит постоянная итерация "изменение Dockerfile, reopen folder in container". Каждый раз генерятся новые докер контейнеры с новыми именами, которые спамят докер.

ЧТО НАДО: чтобы можно было задать имя контейнера. При обновлении Докерфайла должен создаваться контейнер с таким же именем.

**ПРОБЛЕМА: рут юзер в контейнере и файлы**
===========================================

Если создать файл внутри контейнера под рутом, то в хосте этот файл тоже будет принадлежать руту.

ЧТО НАДО: чтобы созданный в контейнере файл принадлежал хост-юзеру. Например, я работаю в хосте под юзером bobby с UID/GID 1000. Я хочу, чтобы юзер в контейнере создавал файлы, которые в хосте имеют такой же UID/GID.

https://code.visualstudio.com/remote/advancedcontainers/add-nonroot-user

You can update or create a Dockerfile that adds a non-root user into your container.

```Dockerfile
ARG USERNAME=user-name-goes-here
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# ********************************************************
# * Anything else you want to do like clean up goes here *
# ********************************************************

# [Optional] Set the default user. Omit if you want to keep the default as root.
USER $USERNAME
```