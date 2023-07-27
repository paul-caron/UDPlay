# UDPlay
Csound udp client. sends music score instructions to a csound server.

20 keys on the keyboard are set to trigger a note, starting with C3 at letter 'q'.

## Requirements
A csound server must be started on localhost, at port 123, with an orchestra file given to it so that it has some instrument definition, like this:

```
csound --port=123 -odac server_orchestra.csd 
```

## Compile
Compile with the compiler of your choice.

For g++:
```
g++ udpclient.cpp -o udplay
```
