extern mod extra;

use std::io::net::ip::SocketAddr;
use std::io::net::tcp::TcpStream;
use std::io::net::addrinfo::get_host_addresses;
use std::str::from_utf8;
use std::to_bytes::ToBytes;
use std::os::args;
use extra::url::Url;



fn main() {
    let url = from_str::<Url>(args()[1]).unwrap();
    let path = match url.path.to_str() { ~"" => {~"/"} s @ _ => {s}};
    let port = match url.port.unwrap().to_str() { ~"" => {~"80"} s @ _ => {s}};
    println(port);
    let ip = get_host_addresses(url.host).unwrap()[0].to_str() + ":" + port;

    let addr = from_str::<SocketAddr>(ip).unwrap();

    let mut sock = TcpStream::connect(addr).unwrap();

    sock.write(("GET " + path + " HTTP/1.0\n\n").to_bytes(true));
    let resp = sock.read_to_end();
    println(from_utf8(resp));
}
