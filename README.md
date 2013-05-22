SPDY-Zeroconf-NGINX
===================
```
upstream backend {
  server 10.0.0.20:8000;
  server 10.0.0.30:8001;
  server 10.0.0.20:8002;
}

server {
  listen 0.0.0.0:80;
  location / {
    proxy_pass https://backend;
  }

```

here we just specified the backend app servers, what if you want to add more later. Tired of restarting right??

## Design Implementation
========================

THe module proxies the http request into SPDY which has explicit implementation for streams and IDs for each in the 
packet. This also paves the way for having chunked requests. 
  The streams are then transmitted via [ZeroMQ XREP/XREQ](http://www.igvita.com/2010/09/03/zeromq-modern-fast-networking-stack/) on the specified port. The worker.rb listens on this port and
then publishes it to all backend servers on their ports via *ZeroMq*.
  When a new server is added is added just change the conf for the worker file and it will add that server along with 
others in the socket pool.

### Resources
=============

Inspired from the prototype work by [@ilya grigorik](https://github.com/igrigorik/zeroconf-router)
