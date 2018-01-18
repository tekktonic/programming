open Http_client.Convenience;;

print_endline (http_get "https://suckless.org/index.html");;
