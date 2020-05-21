*For question #1:*

`The packages highlighted in gray are the connection (Having 'SYN' or 'SYN, ACK'),`
`the transmission (Having 'PSH', 'ACK'), and the closing connection (Having 'FIN','ACK')`

*To get a better view at these, right-click on these two:*
`1	0.000000000	127.0.0.1	127.0.0.1	TCP	76	43210 → 5431 [SYN] Seq=0 Win=65495 Len=0 MSS=65495 SACK_PERM=1 TSval=1843139886 TSecr=0 WS=128`
`4	5.867405905	127.0.0.1	127.0.0.1	TCP	76	43212 → 5431 [SYN] Seq=0 Win=65495 Len=0 MSS=65495 SACK_PERM=1 TSval=1843145753 TSecr=0 WS=128`

*Go to 'Conversation Filter', and select TCP for each one. This will only select the entries we care about.*
