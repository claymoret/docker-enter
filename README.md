# docker-enter

A tool use `nsenter` to open a shell in a docker with container id.

## Run

If you are not care about the environments, just run docker-enter. 

```
docker-enter CONTAINER [COMMAND [ARG]...]
```
## Examples
To open a shell
```
docker-enter ac2f8bde5d5f
```

Run command instead of enter the docker
```
docker-enter ac2f8bde5d5f ls -l
```

# importenv

A util to load environments before you enter the docker.

When it's used with docker-enter, you just need to build it and leave it there. It can also be used alone.

## Compile

It's a simple program written in C. 
```
make
```

## Install
To install this tool to /usr/local/bin
```
make install
```
## Use it alone

Run the util alone can:
* get the environments of a process.
* set the environments and run COMMAND.
```
sudo ./importenv <pid|environ-file> [COMMAND [ARG]...]
```




