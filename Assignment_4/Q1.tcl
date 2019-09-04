set ns [new Simulator] ;# Letter S is capital
set nf [open PA1.nam w] ;# open a nam trace file in write mode
$ns namtrace-all $nf ;# nf nam filename
set tf [open PA1.tr w] ;# tf trace filename
$ns trace-all $tf
proc finish { } {
global ns nf tf
$ns flush-trace ;# clears trace file contents
close $nf
close $tf
exec nam PA1.nam &
exit 0
}
set n0 [$ns node] ;# creates 3 nodes
set n2 [$ns node]
set n3 [$ns node]
$ns duplex-link $n0 $n2 1Mb 10ms DropTail ;# establishing links
$ns duplex-link $n2 $n3 700kb 10ms DropTail
$ns queue-limit $n0 $n2 5
$ns queue-limit $n2 $n3 5
set udp0 [new Agent/UDP] ;# attaching transport layer protocols
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR] ;# attaching application layer protocols
$cbr0 set packetSize_ 1500
$cbr0 set interval_ 0.01
$cbr0 attach-agent $udp0
set null0 [new Agent/Null] ;# creating sink(destination) node
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0
$ns at 0.1 "$cbr0 start"
$ns at 1.0 "finish"
$ns run
