(require-extension http-client)
(require-extension irc)

(require-extension irregex)

(define channel "##valix-offtopic")
(define connection (irc:connection server: "irc.freenode.net" nick: "botname" password: "pass"))
(define extract-urls
  (lambda (m)
    (irregex-extract (string->irregex "(http|https)://[^\\s]+") m)))

(irc:add-message-handler! 
 connection 
 (lambda (m)
   (let ((urls (extract-urls (irc:message-body m))))
     (display urls)
     (newline)
     (for-each 
      (lambda (u) 
	(display u) (newline) 
	(irc:say connection (with-input-from-request "http://s.tekk.in/submit" `((url . ,u))
			 read-string))) urls)))
 command: "PRIVMSG" body: (lambda (m) (not (eq? (extract-urls (irc:message-body m)) '()))))


(irc:run-message-loop connection)

