extern crate openssl;
use std::net::TcpStream;
use openssl::ssl::{Ssl, SslStream, SslContext, SslMethod};

fn main()
{
    let meth = SslMethod::Tlsv1_2;
    let mut sslctx = SslContext::new(meth).unwrap();
    let mut ssl = Ssl::new(&sslctx).unwrap();
    let mut tcpsock = TcpStream::connect("duckduckgo.com:443").unwrap();
    let mut socket = SslStream::connect(ssl, tcpsock).unwrap();
}
