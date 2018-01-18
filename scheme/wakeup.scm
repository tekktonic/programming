(require-extension dbus)
(register-signal-handler session-bus "im.pidgin.purple.PurpleInterface.ReceivedImMsg" (lambda (acc sen msg conv flags) (display "howdy there neighbor!")(newline)))
