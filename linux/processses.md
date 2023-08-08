### Find process that is using a particular port

```
$ sudo netstat -nlp | grep 9229
tcp        0      0 127.0.0.1:9229          0.0.0.0:*               LISTEN      859/node
```
