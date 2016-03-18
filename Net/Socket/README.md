#Socket
对Socket的封装

TCP的使用:
```
TCP sender code

#include"../Net/Socket/Socket.h"

int main(int argc, char *argv[]){
    NetworkLib::Socket::TCP server;
    server.connect_to(NetworkLib::Socket::Address("127.0.0.1", 8000));
    return EXIT_SUCCESS;
}

```

```
TCP receiver code

#include"../Net/Socket/Socket.h"

int main(int argc, char *argv[]){
    NetworkLib::Socket::TCP server;

    server.listen_on_port(8000);
    NetworkLib::Socket::TCP client = server.accept_client();

    return EXIT_SUCCESS;
}

```

UDP的使用:
```
UDP sender code

#include"../Net/Socket/Socket.h"

int main(int argc, char *argv[]){

    return EXIT_SUCCESS;
}


```

```
UDP receiver code
#include"../Net/Socket/Socket.h"

int main(int argc, char *argv[]){

    return EXIT_SUCCESS;
}
```
