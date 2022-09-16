# About a Strange WireGuard Reconnection Bug

I don't think it's a bug of the firmware, the reason is the device was behind a big NAT network.

The thing will happen after the device lost wifi connection for about half an hour. Though the wifi reconnected, device cannot reconnect to the wireguard server.

You can read the dmesg from server side, unrelated messages were deleted.

```
[11481760.861169] wireguard: wg0server: Receiving handshake initiation from peer 213 (112.224.70.218:20109)
[11481760.861172] wireguard: wg0server: Sending handshake response to peer 213 (112.224.70.218:20109)
[11481760.861316] wireguard: wg0server: Keypair 26512 destroyed for peer 213
[11481760.861317] wireguard: wg0server: Keypair 26519 created for peer 213
[11481760.989045] wireguard: wg0server: Receiving keepalive packet from peer 213 (112.224.70.218:20109)
[11481790.914581] wireguard: wg0server: Sending keepalive packet to peer 208 (112.224.70.218:20110)
[11481796.290322] wireguard: wg0server: Retrying handshake with peer 213 (112.224.70.218:20109) because we stopped hearing back after 15 seconds
[11481796.290332] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481801.410077] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 2)
[11481801.410087] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481806.785820] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 3)
[11481806.785862] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481812.161564] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 4)
[11481812.161579] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481815.980668] wireguard: wg0server: Receiving keepalive packet from peer 208 (112.224.70.218:20110)
[11481817.537305] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 5)
[11481817.537373] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481822.913044] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 6)
[11481822.913062] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481826.824920] wireguard: wg0server: Keypair 26506 destroyed for peer 206
[11481826.824921] wireguard: wg0server: Keypair 26520 created for peer 206
[11481828.032800] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 7)
[11481828.032814] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481833.152553] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 8)
[11481833.152569] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481838.272306] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 9)
[11481838.272323] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481840.979418] wireguard: wg0server: Receiving keepalive packet from peer 208 (112.224.70.218:20110)
[11481843.392062] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 10)
[11481843.392078] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481848.511815] wireguard: wg0server: Handshake for peer 213 (112.224.70.218:20109) did not complete after 5 seconds, retrying (try 11)
[11481848.511828] wireguard: wg0server: Sending handshake initiation to peer 213 (112.224.70.218:20109)
[11481850.116924] wireguard: wg0server: Receiving handshake response from peer 213 (112.224.70.218:20109)
[11481850.116931] wireguard: wg0server: Keypair 26518 destroyed for peer 213
[11481850.116932] wireguard: wg0server: Keypair 26521 created for peer 213
```

But the client side did not receive anything.

The client side wifi connection is the hotspot of my smartphone, and my smartphone was connected to China Unicom LTE.

Here is the log from client side, I inserted some log node in the [WireGuard-ESP32](https://github.com/ciniml/WireGuard-ESP32-Arduino) code.

You can see, after switching the network, the device received packages from server and handshake completed.

It is the NAT to be claim.

```
Start wg: [  4506][I][WireGuard.cpp:76] begin(): [WireGuard] wg.youmu.love is xxx. xx.xxx. xx
[  4506][I][wireguardif.c:961] wireguardif_init(): [WireGuard] underlying_netif = 0x3ffaf6e0
[  4511][I][wireguardif.c:968] wireguardif_init(): [WireGuard] wireguard module initialized.
[  4519][D][wireguardif.c:993] wireguardif_init(): [WireGuard] start device initialization
[  4560][D][wireguardif.c:998] wireguardif_init(): [WireGuard] Device init took 33ms

[  4595][I][wireguardif.c:804] wireguardif_add_peer(): [WireGuard] Adding peer took 32ms

[  4595][V][WireGuard.cpp:108] begin(): [WireGuard] Add peer success.
[  4598][I][WireGuard.cpp:113] begin(): [WireGuard] connecting wireguard...
[  4605][V][WireGuard.cpp:115] begin(): [WireGuard] wgif connect success.
done.
[  4960][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[  4960][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[  4965][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[  5041][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[  5042][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[  5047][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[  5056][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[  5064][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[  5072][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  5360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  5760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  6160][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  6560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  6960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  7360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  7760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  8160][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  8560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  8960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  9360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[  9760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 10160][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[ 10160][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[ 10165][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[ 10241][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[ 10242][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[ 10247][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[ 10256][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[ 10264][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[ 10272][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 10560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 10960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 11360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 11760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 12160][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 12560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 12960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 13360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 13760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 14160][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 14560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 14960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 15360][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[ 15360][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[ 15365][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[ 15441][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[ 15442][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[ 15447][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[ 15456][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[ 15464][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[ 15472][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 15760][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 16160][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 16560][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 16960][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[ 17360][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[278962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[279362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[279762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[280162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[280562][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[280562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[280567][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[280642][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[280644][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[280648][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[280657][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[280665][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[280673][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[280962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[281362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[281762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[282162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[282562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[282962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[283362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[283762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[470962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[471362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[471762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[472162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[472562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[472962][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[472962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[472967][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[473042][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[473043][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[473048][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[473057][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[473065][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[473073][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[473362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[473762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[474162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[474562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[474962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[475362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[475762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[476162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[476562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[476962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[477362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[477762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[478162][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[478162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[478167][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[478242][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[478243][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[478248][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[478257][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[478265][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[478273][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[478562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[478962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[479362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[479762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[480162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[480562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[480962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[481362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[481762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[482162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[482562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[482962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[483362][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[483362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[483367][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[483443][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[483444][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[483449][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[483458][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[483466][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[483474][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[483762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[484162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[484562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[484962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[485362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[485762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[486162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[486562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[486962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[487362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[487762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[488162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[488562][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[488562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[488567][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[488643][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[488644][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[488649][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[488658][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[488666][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[488674][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[488962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[489362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[489762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[490162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[490562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[490962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[491362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[491762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[492162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[492562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[492962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[493362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[493762][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[493762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[493767][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[493843][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[493844][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[493849][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[493858][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[493866][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[493874][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[494162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[494562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[494962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[495362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[495762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[496162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[496562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[496962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[497362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[497762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[498162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[498562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[498962][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[498962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[498967][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[499042][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[499043][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[499048][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[499057][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[499065][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[499073][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[499362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[499762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[500162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[500562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[500962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[501362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[501762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[502162][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[502562][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[502962][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.           <---------- I switched network about here
[503362][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[503762][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[504162][V][wireguardif.c:826] should_send_initiation(): [WireGuard] 3 true
[504162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[504167][V][wireguardif.c:902] wireguardif_tmr(): [WireGuard] Should send initiation.
[504243][V][wireguardif.c:642] wireguard_start_handshake(): [WireGuard] pbuf is not empty
[504244][I][wireguardif.c:644] wireguard_start_handshake(): [WireGuard] start handshake 1bc03778,9001 - 0
[504249][V][wireguardif.c:906] wireguardif_tmr(): [WireGuard] Wireguard start handshake returned success.
[504258][V][wireguardif.c:909] wireguardif_tmr(): [WireGuard] current keypair not invalid.
[504266][V][wireguardif.c:912] wireguardif_tmr(): [WireGuard] prev keypair not invalid.
[504274][V][wireguardif.c:920] wireguardif_tmr(): [WireGuard] Wireguard link not up.
[504306][V][wireguardif.c:563] wireguardif_network_rx(): [WireGuard] Wireguard receive message from network.        <---------- Messages from server received
[504307][V][wireguardif.c:566] wireguardif_network_rx(): [[WireGuard] ] network_rx: 1bc03778:9001
[504314][I][wireguardif.c:587] wireguardif_network_rx(): [WireGuard] HANDSHAKE_RESPONSE: 1bc03778:9001
[504390][I][wireguardif.c:220] wireguardif_process_response_message(): [WireGuard] good handshake from 1bc03778:9001
[504391][V][wireguardif.c:223] wireguardif_process_response_message(): [WireGuard] Wg start session.
[504399][V][wireguardif.c:136] wireguardif_output_to_peer(): [WireGuard] preparing transport data...
[504562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[504962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[505362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[505762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[506162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[506562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[506962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[507362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[507762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[508162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[508562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[508962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[509362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[509362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[509762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[509762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[510162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[510162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[510562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[510562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[510962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[510962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[511362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[511362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[511762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[511762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[512162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[512162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[512562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[512562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[512962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[512962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[513362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[513362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[513762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[513762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[514162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[514162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[514562][V][wireguardif.c:898] wireguardif_tmr(): [WireGuard] Should send keepalive.
[514562][V][wireguardif.c:136] wireguardif_output_to_peer(): [WireGuard] preparing transport data...
[514569][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[514576][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[514962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[514962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[515362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[515362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[515762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[515762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[516162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[516162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[516562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[516562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[516962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[516962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[517362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[517362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[517762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[517762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[518162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[518162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[518562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[518562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[518962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[518962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[519362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[519362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[519762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[519762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[520162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[520162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[520562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[520562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[520962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[520962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[521362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[521362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[521762][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[521762][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[522162][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[522162][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[522562][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[522562][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[522962][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[522962][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
[523362][V][wireguardif.c:829] should_send_initiation(): [WireGuard] Wireguardif can send initiation.
[523362][V][wireguardif.c:918] wireguardif_tmr(): [WireGuard] Wireguard link up.
```


