# tinyweb

a from-scratch, highly modular http/1.1 server written in raw c. operating entirely on top of posix sockets, **tinyweb** bypasses standard library crutches to demonstrate low-level network i/o, custom memory-managed data structures, and multithreaded request handling.

## why tinyweb?
- **byo data structures**: ships with its own custom `structs` namespace covering singly linked lists, binary trees, dictionaries (hash maps), and queues.
- **embedded threadpool**: integrates a condition-variable based executor for concurrent, non-blocking connection handling.
- **variadic routing engine**: features a custom uri router mapping http verbs directly to function pointer callbacks.

> [!WARNING]
> tinyweb is an educational deep dive into raw socket programming, manual http lexing, and concurrency primitives. it is not hardened against malformed packets or slowloris attacks and should not be exposed to the open web.

## table of contents
- [architecture & request lifecycle](#architecture--request-lifecycle)
- [project structure](#project-structure)
- [features](#features)
- [component breakdown](#component-breakdown)

***

## architecture & request lifecycle
at the foundation, the `server` struct manages the posix triad: `socket()`, `bind()`, and `listen()`. the `http` layer wraps this raw tcp server, providing an application interface to register routes and parse incoming packet buffers.

1. **acceptance**: the main thread blocks on `accept()`, awaiting inbound client tcp handshakes.
2. **offload**: upon connection, the client socket descriptor is packaged as an `exec_work` payload and dispatched to the thread pool queue.
3. **lexing**: a worker thread wakes, reads the socket descriptor into a heap buffer, and passes it to the `parser`. the parser extracts the http verb, uri, protocol version, and headers.
4. **routing**: the requested uri is hashed and queried against the internal `dict` of registered routes.
5. **execution**: the associated function pointer is invoked with the populated `request` context. the handler generates the http response and flushes the buffer down the socket descriptor before closing the connection.

> [!NOTE]
> all dynamic memory allocations for an individual request are strictly scoped to the worker thread's execution cycle, ensuring clean garbage collection upon socket closure.

## project structure
```text
tinyweb/
├── include/
│   ├── server/          # web server core
│   │   ├── executor.h   # concurrency and worker pool definitions
│   │   ├── http.h       # high-level http server state and routing
│   │   ├── parser.h     # http request buffer parsing logic
│   │   ├── route.h      # route metadata mapping
│   │   ├── server.h     # raw posix socket wrapper
│   │   └── thread.h     # base threading primitives
│   └── structs/         # custom data structure headers
│       ├── dict/        # hash map for fast route lookups
│       ├── queue/       # fifo queue for the thread pool
│       ├── slist/       # singly linked list nodes
│       └── tree/        # binary tree representations
├── src/
│   ├── server/          # core implementations (executor.c, http.c, etc)
│   └── structs/         # data structure implementations
├── makefile             # build automation
├── req.py               # request generation script
└── readme.md
```

## features
- **dynamic router**: register rest endpoints utilizing `register_route()`, supporting variadic parameters to bind multiple http methods to a single uri.
- **asynchronous execution**: a synchronized worker pool intercepts client connections, processing multiple clients concurrently without stalling the main event loop.
- **template rendering**: provides `render_func()`, a variadic function to dynamically stitch together modular html components before transmission.
- **raw sockets**: highly configurable socket domains (e.g., `af_inet`), protocols, and listen backlog sizing.

## component breakdown

### the parser
the parser takes raw socket byte streams and tokenizes them. it separates the request line from the headers by hunting for `\r\n\r\n`, extracting the headers into a key-value dictionary for easy lookup by the route handlers.

### the executor
a posix-compliant thread pool implementation. threads block on `pthread_cond_wait` until the main server thread dispatches a new client socket into the fifo `queue`.

### the dictionary (hash map)
used extensively for o(1) lookups during routing. uris are hashed and mapped to their respective `route` structs, which encapsulate the supported http methods and the target function pointer callback.
