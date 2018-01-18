extern crate crypto;
extern crate rand;
extern crate json;
extern crate rustc_serialize;

use std::env::home_dir;
use std::io;
use std::io::prelude::*;
use std::fs::File;
use std::fs::OpenOptions;
use std::path::PathBuf;
use std::str;

use crypto::aes;
use crypto::aes::{KeySize, ctr};
use crypto::symmetriccipher::{Encryptor,Decryptor,SynchronousStreamCipher};
use crypto::buffer;
use json::{parse};
use rand::{OsRng, Rng};
use rustc_serialize::base64::{ToBase64, STANDARD};

fn setup_crypto() -> Box<SynchronousStreamCipher> {
    let mut rng = OsRng::new().ok().expect("RNG instantiation failed");
    let mut key = String::new();
    io::stdin().read_line(&mut key).ok();
    key = key.trim().to_string();
    println!("Key is: {}", key);

    let mut nonce = vec![0u8, 32];
    rng.fill_bytes(nonce.as_mut_slice());
    let mut engine = aes::ctr(KeySize::KeySize256, key.as_bytes(), nonce.as_slice());

    return engine;
}
fn main() {
    let mut crypt = setup_crypto();
    
    let mut ctext = String::new();
    io::stdin().read_line(&mut ctext).ok();
    ctext = ctext.trim().to_string();

    let mut buf_encrypted = vec![0u8; ctext.len() * 4];
    let mut buf_decrypted = vec![0u8; ctext.len() * 4];
    {
        let mut rbuf = buffer::RefReadBuffer::new(ctext.as_bytes());

        let mut wbuf = buffer::RefWriteBuffer::new(&mut buf_encrypted);

        crypt.encrypt(&mut rbuf, &mut wbuf, false);
    }
    println!("{} was the result", buf_encrypted.to_base64(STANDARD));
    {
        let mut rbuf = buffer::RefReadBuffer::new(buf_encrypted.as_slice());

        let mut wbuf = buffer::RefWriteBuffer::new(&mut buf_decrypted);

        crypt.decrypt(&mut rbuf, &mut wbuf, false);
    }

    println!("After decrypting {:?}, {:?} we got {:?}", ctext.as_bytes(), buf_encrypted, buf_decrypted);
}
