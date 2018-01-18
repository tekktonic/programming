(require-extension irc)

(define channel "#zacts")
(define connection (irc:connection server: "irc.freenode.net" nick: "scbot"))
(irc:connect connection)
(irc:join connection channel)

(irc:say connection "oi!" channel)

(irc:run-message-loop connection)
