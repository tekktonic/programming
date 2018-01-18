#![feature(convert)]

use std::thread;
use std::io::Read;
use std::io::Write;
use std::sync::{Arc, Mutex};
use std::sync::mpsc::{channel, Sender, Receiver};
use std::string::String;
use std::net::{TcpListener, TcpStream};

use std::vec::{Vec};

fn handle_client_sends(mut stream: TcpStream, c_send: Sender<String>)
{

    loop {
        let mut buffer = &mut [0; 256];
        let mut v = Vec::new();
        let _ = stream.read(buffer);
        println!("Received something");
        v.extend_from_slice(buffer);
        let _ = stream.write(buffer);
        c_send.send(String::from_utf8(v).unwrap()).unwrap();
    }
}


fn handle_client_receives(mut stream: TcpStream, c_recv: Receiver<String>)
{
    for msg in c_recv.iter() {
        println!("Received a message");
        let _ = stream.write(msg.into_bytes().as_slice());
        println!("sent message");
    }
}

fn handle_connections(c_send: Sender<String>, mut s_senders: Arc<Mutex<Vec<Sender<String>>>>)
{
    let listener = TcpListener::bind("127.0.0.1:1453").unwrap();
    
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let stream_clone = stream.try_clone().unwrap();
                let send_clone = c_send.clone();
                let (send, receive) = channel::<String>();
                {
                    let senders_mtx = s_senders.lock();
                    senders_mtx.unwrap().push(send);
                }
//                println!("{}", s_senders.read().unwrap().is_empty());
                thread::spawn(move||{handle_client_sends(stream, send_clone)});
                thread::spawn(move||{handle_client_receives(stream_clone, receive)});
            }
            Err(e) => { println!("unable to connect"); }
        }
    }

    drop(listener);
}
fn main() {
    let (client_send, server_receive) = channel::<String>();
    let mut client_pipes: Arc<Mutex<Vec<Sender<String>>>> = Arc::new(Mutex::new(Vec::new()));

    {
        let client_send_clone = client_send.clone();
        let client_pipes_clone = client_pipes.clone();
        thread::spawn(move||{handle_connections(client_send_clone, client_pipes_clone)});
    }
    loop {
        for msg in server_receive.iter() {
            let mut senders_mtx = client_pipes.lock().unwrap();

            for client in senders_mtx.iter() {
                println!("{}", msg);
//                client.send(String::from(msg);
            }
        }
        println!("mainloop");
    }
}
