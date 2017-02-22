========================================
RPC
========================================


.. contents:: 目錄


介紹
========================================

什麼是 RPC ？
------------------------------

RPC 的全名叫 Remote Procedure Call，
是一種 IPC 的機制，
藉由這個機制可以讓程式的部份工作交由不同的程式處理，
負責處理的程式可以在別臺機器上用不同的語言撰寫，
最後在透過這機制回傳結果即可，
而程式間互相合作得就好像跑在同一隻程式一樣。

RPC 的概念和理論出現在 1960 到 1970 年代，
概念為藉由 request-response 溝通協議來處理程式間的同步問題，
而第一個熱門的 RPC 實做為 1980 年代的 Sun RPC，
其應用在 NFS （Network File System）上。
到了 1990 年代則出現隨著物件導向的熱潮出現了替代的方案 RMI （Remote Metnode Invocation），
相關實做如 CORBA（Common Object Request Broker Architecture）、Java RMI，
RMI 的作法後來隨著在 2000 年代隨著網路發展而漸漸末落，

RPC 是一種 request-response protocol，
client 端送訊息到遠端伺服器要求執行某些程式，
遠端伺服器執行完後再回傳結果給 client 端，
client 端收到回應後就繼續執行剩下的工作。
為了讓 client 和 server 可以溝通，
通常會使用特製的 IDL （Interface Descroption Language）來描述溝通界面，
而 IDL 程式碼則可以用來生成 client 和 server 要使用的界面程式碼。


什麼是 gRPC ？
------------------------------

gRPC 是一套 Google 開發的 RPC Framework，
預設是使用 Protocol Buffers 來處理 Serialization（也可以用其他格式，例如 JSON）。


使用的三個步驟：

* 此用 IDL 定義要溝通的東西（Protocol Buffers）
* 使用 IDL 的編譯器生成需要的程式碼
* 基於生成的程式碼開發 Client/Server


安裝：

.. code-block:: sh

    $ pip install grpcio grpcio-tools


撰寫 IDL：

.. code-block:: proto

    // sample.proto

    syntax = "proto3";

    // The greeter service definition.
    service Greeter {
        // Sends a greeting
        rpc SayHello (HelloRequest) returns (HelloReply) {}
    }

    // The request message containing the user's name.
    message HelloRequest {
        string name = 1;
    }

    // The response message containing the greetings
    message HelloReply {
        string message = 1;
    }


生成 gRPC 需要的程式碼：

.. code-block:: sh

    # generate *_pb2.py which contains request and response classes
    # generate and *_pb2_grpc.py which contains client and server classes (stub)
    $ python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. sample.proto


撰寫 Client/Server 程式碼：

.. code-block:: python

    # myclient.py

    import grpc
    import sample_pb2
    import sample_pb2_grpc


    def run():
        channel = grpc.insecure_channel('localhost:50051')
        stub = sample_pb2_grpc.GreeterStub(channel)
        response = stub.SayHello(sample_pb2.HelloRequest(name='Hsiang'))
        print("Greeter client received: " + response.message)


    if __name__ == '__main__':
        run()


.. code-block:: python

    # myserver.py

    from concurrent import futures
    import time
    import grpc
    import sample_pb2
    import sample_pb2_grpc

    _ONE_DAY_IN_SECONDS = 60 * 60 * 24


    class Greeter(sample_pb2_grpc.GreeterServicer):
        def SayHello(self, request, context):
            return sample_pb2.HelloReply(message=f'Hello, {request.name}!')


    def serve():
        server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        sample_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
        server.add_insecure_port('[::]:50051')
        server.start()
        try:
            while True:
                time.sleep(_ONE_DAY_IN_SECONDS)
        except KeyboardInterrupt:
            server.stop(0)

    if __name__ == '__main__':
        serve()



什麼是 Protocol Buffers ？
------------------------------

Protocol Buffers 是一套資料 Serialization 的方法，
可以用於資料的儲存或傳輸，
其設計是為了簡化和加速原本由 XML 負責的部份，
格式為 Binary 而非 Plain Text，
尤其廣泛使用於 RPC 系統。


安裝：

.. code-block:: sh

    $ sudo pacman -S protobuf


範例：

.. code-block:: proto

    syntax = "proto3";

    message Person {
        string name = 1;
        int32 id = 2;
        bool has_ponycopter = 3;
    }


.. code-block:: sh

    $ mkdir gen
    $ protoc --cpp_out=gen/ sample.proto
    $ ls gen/
    sample.pb.cc  sample.pb.h


範例：

.. code-block:: proto

    syntax = "proto3";

    // The greeter service definition.
    service Greeter {
        // Sends a greeting
        rpc SayHello (HelloRequest) returns (HelloReply) {}
    }

    // The request message containing the user's name.
    message HelloRequest {
        string name = 1;
    }

    // The response message containing the greetings
    message HelloReply {
        string message = 1;
    }


.. code-block:: sh

    $ mkdir gen
    $ protoc --cpp_out=gen/ sample.proto
    $ ls gen/
    sample.pb.cc  sample.pb.h


支援的語言（可以擴充）：

* C++
* C#
* Java
* Java Nano
* JavaScript
* Objective-C
* PHP
* Python
* Ruby
* `Go <https://github.com/golang/protobuf>`_
* `C <https://github.com/protobuf-c/protobuf-c>`_
* `Rust <https://github.com/stepancheg/rust-protobuf>`_



什麼是 Cap'n Proto ？
------------------------------

Cap'n Proto 是 Protocol Buffers v2 的作者後來開發的專案，
作者吸收先前的經驗來開發新的 Serialization 格式，
主打有更好的效率。


什麼是 FlatBuffers ？
------------------------------

什麼是 MessagePack ？
------------------------------

MessagePack RPC 使用者：

* Neovim



選擇 Serialization 方案
========================================

在選擇一個方案的時候會有很多考量，
不同的實做間有不同的 tradeoff，
選擇適合自己的使用情境的方案就變成一個問題。

可能的考量：

* Serialization/Deserialization 效能
* 需要的儲存大小
* 傳輸需要的頻寬
* 支援的程式語言數量
* 特定程式語言的支援
* 支援的平台數量
* 特定平台的支援
* 可讀性
* 生態圈的豐富度和活躍度


例如：
Cap'n Proto 在 Serialization/Deserialization 效能考量下可能就是個很好的選擇，
但是它是 Binary 格式，
如果你要良好的可讀性的話，
可能就得選擇其他 Plain Text 的方案。



相關專案
========================================

* D-Bus
* XML-RPC
* JSON-RPC
* Apache Thrift
* CORBA
* Libevent
* gRPC
* Erlang



參考
========================================

* `Wikipedia - Remote Procedure Call <https://en.wikipedia.org/wiki/Remote_procedure_call>`_
* `Wikipedia - Comparison of data serialization formats <https://en.wikipedia.org/wiki/Comparison_of_data_serialization_formats>`_

gRPC：

* `gRPC - A high performance, open source universal RPC framework <http://www.grpc.io/>`_
* [GitHub] `gRPC <https://github.com/grpc/grpc/>`_
* `Introducing gRPC, a new open source HTTP/2 RPC Framework <https://developers.googleblog.com/2015/02/introducing-grpc-new-open-source-http2.html>`_


Protocol Buffers：

* `Protocol Buffers <https://developers.google.com/protocol-buffers/>`_
* [GitHub] `Protocol Buffers <https://github.com/google/protobuf>`_


Cap'n Proto：

* `Cap'n Proto - Introduction <https://capnproto.org/>`_
* [GitHub] `Cap'n Proto for Rust <https://github.com/dwrensha/capnproto-rust>`_
* `Cap'n Proto, FlatBuffers, and SBE <https://capnproto.org/news/2014-06-17-capnproto-flatbuffers-sbe.html>`_


FlatBuffers：

* `FlatBuffers <http://google.github.io/flatbuffers/index.html>`_
* `Improving Facebook's performance on Android with FlatBuffers <https://code.facebook.com/posts/872547912839369/improving-facebook-s-performance-on-android-with-flatbuffers/>`_



Benchmark：

* `REST v.s. gRPC <https://husobee.github.io/golang/rest/grpc/2016/05/28/golang-rest-v-grpc.html>`_
* `Rewriting Rust Serialization, Part 3: Introducing Serde <http://erickt.github.io/blog/2014/12/13/rewriting-rust-serialization/>`_
    - Cap'n Proto, Protocol Buffers, MessagePack, JSON
