#### i really don't recommend you to read this.

u_long <var> : means it'll store only positive values, and fun fact if you store -ve value anyways it'll wrap around it and return the longest number it can store (since my device is x64 it'll return biggest number 64 bits can handle).
also u_long and unsigned_long are same. one is portable and other is kept for compatability with old APIs.

<sys/socket.h> : gives multiple stuff but mainly: socklen_t, which is an unsigned opaque integral type of length of at least 32 bits. here opaque means that it doesn't matter if the type uses 32 or 64 bits. the endianness: order the bits are stored also don't matter and the interpretation by complier.. none of it matters it'll handle it all on it's own. the api will abstract away all these complexities.


sockaddr/sockaddr_in/sockaddr_in6 confusion: 