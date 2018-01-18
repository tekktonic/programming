import Network
import System.IO
import Text.Printf

server = "irc.freenode.org"
port   = 6667
 
main = do
    h <- connectTo "irc.freenode.net" (PortNumber (fromIntegral 6667))
    hSetBuffering h NoBuffering 
    hPrintf h "%s %s\r\n" "NICK" "NotTekk"
    hPrintf h "%s %s\r\n" "USER" "NotTekk 0 * :Tekk"
    hPrintf h "%s %s\r\n" "JOIN" "#dagd"
    hPrintf h "%s %s\r\n" "PART" "#dagd"
    t <- hGetContents h
    print t