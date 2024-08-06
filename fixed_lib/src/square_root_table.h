#pragma once
// generated on Jan  5 2021 12:53:44
#include <fixedmath/types.h>

#include <cstdio>
#include <array>
#include <cstdint>
#include <cassert>

namespace fixedmath {

// square root precalculated values
static std::array<uint16_t, 256> square_root_table__ {

  0x2c8 /* sqrt(0.000118256) ~=0.0108642578125000*/,   0x103d /* sqrt(0.0040245056152344) ~=0.0634307861328125*/, 
  0x16cc /* sqrt(0.0079307556152344) ~=0.0890502929687500*/,   0x1bda /* sqrt(0.0118370056152344) ~=0.1087951660156250*/, 
  0x201f /* sqrt(0.0157432556152344) ~=0.1254730224609375*/,   0x23e2 /* sqrt(0.0196495056152344) ~=0.1401672363281250*/, 
  0x274a /* sqrt(0.0235557556152344) ~=0.1534729003906250*/,   0x2a6c /* sqrt(0.0274620056152344) ~=0.1657104492187500*/, 
  0x2d57 /* sqrt(0.0313682556152344) ~=0.1771087646484375*/,   0x3014 /* sqrt(0.0352745056152344) ~=0.1878051757812500*/, 
  0x32ac /* sqrt(0.0391807556152344) ~=0.1979370117187500*/,   0x3523 /* sqrt(0.0430870056152344) ~=0.2075653076171875*/, 
  0x377e /* sqrt(0.0469932556152344) ~=0.2167663574218750*/,   0x39c1 /* sqrt(0.0508995056152344) ~=0.2256011962890625*/, 
  0x3bee /* sqrt(0.0548057556152344) ~=0.2341003417968750*/,   0x3e07 /* sqrt(0.0587120056152344) ~=0.2422943115234375*/, 
  0x400f /* sqrt(0.0626182556152344) ~=0.2502288818359375*/,   0x4207 /* sqrt(0.0665245056152344) ~=0.2579193115234375*/, 
  0x43f0 /* sqrt(0.0704307556152344) ~=0.2653808593750000*/,   0x45cc /* sqrt(0.0743370056152344) ~=0.2726440429687500*/, 
  0x479b /* sqrt(0.0782432556152344) ~=0.2797088623046875*/,   0x495f /* sqrt(0.0821495056152344) ~=0.2866058349609375*/, 
  0x4b19 /* sqrt(0.0860557556152344) ~=0.2933502197265625*/,   0x4cc8 /* sqrt(0.0899620056152344) ~=0.2999267578125000*/, 
  0x4e6e /* sqrt(0.0938682556152344) ~=0.3063659667968750*/,   0x500c /* sqrt(0.0977745056152344) ~=0.3126831054687500*/, 
  0x51a1 /* sqrt(0.1016807556152344) ~=0.3188629150390625*/,   0x532f /* sqrt(0.1055870056152344) ~=0.3249359130859375*/, 
  0x54b5 /* sqrt(0.1094932556152344) ~=0.3308868408203125*/,   0x5635 /* sqrt(0.1133995056152344) ~=0.3367462158203125*/, 
  0x57ae /* sqrt(0.1173057556152344) ~=0.3424987792968750*/,   0x5920 /* sqrt(0.1212120056152344) ~=0.3481445312500000*/, 
  0x5a8d /* sqrt(0.1251182556152344) ~=0.3537139892578125*/,   0x5bf4 /* sqrt(0.1290245056152344) ~=0.3591918945312500*/, 
  0x5d56 /* sqrt(0.1329307556152344) ~=0.3645935058593750*/,   0x5eb2 /* sqrt(0.1368370056152344) ~=0.3699035644531250*/, 
  0x600a /* sqrt(0.1407432556152344) ~=0.3751525878906250*/,   0x615d /* sqrt(0.1446495056152344) ~=0.3803253173828125*/, 
  0x62ab /* sqrt(0.1485557556152344) ~=0.3854217529296875*/,   0x63f5 /* sqrt(0.1524620056152344) ~=0.3904571533203125*/, 
  0x653b /* sqrt(0.1563682556152344) ~=0.3954315185546875*/,   0x667c /* sqrt(0.1602745056152344) ~=0.4003295898437500*/, 
  0x67ba /* sqrt(0.1641807556152344) ~=0.4051818847656250*/,   0x68f4 /* sqrt(0.1680870056152344) ~=0.4099731445312500*/, 
  0x6a2b /* sqrt(0.1719932556152344) ~=0.4147186279296875*/,   0x6b5e /* sqrt(0.1758995056152344) ~=0.4194030761718750*/, 
  0x6c8d /* sqrt(0.1798057556152344) ~=0.4240264892578125*/,   0x6db9 /* sqrt(0.1837120056152344) ~=0.4286041259765625*/, 
  0x6ee2 /* sqrt(0.1876182556152344) ~=0.4331359863281250*/,   0x7008 /* sqrt(0.1915245056152344) ~=0.4376220703125000*/, 
  0x712b /* sqrt(0.1954307556152344) ~=0.4420623779296875*/,   0x724c /* sqrt(0.1993370056152344) ~=0.4464721679687500*/, 
  0x7369 /* sqrt(0.2032432556152344) ~=0.4508209228515625*/,   0x7483 /* sqrt(0.2071495056152344) ~=0.4551239013671875*/, 
  0x759b /* sqrt(0.2110557556152344) ~=0.4593963623046875*/,   0x76b1 /* sqrt(0.2149620056152344) ~=0.4636383056640625*/, 
  0x77c4 /* sqrt(0.2188682556152344) ~=0.4678344726562500*/,   0x78d4 /* sqrt(0.2227745056152344) ~=0.4719848632812500*/, 
  0x79e2 /* sqrt(0.2266807556152344) ~=0.4761047363281250*/,   0x7aee /* sqrt(0.2305870056152344) ~=0.4801940917968750*/, 
  0x7bf7 /* sqrt(0.2344932556152344) ~=0.4842376708984375*/,   0x7cfe /* sqrt(0.2383995056152344) ~=0.4882507324218750*/, 
  0x7e03 /* sqrt(0.2423057556152344) ~=0.4922332763671875*/,   0x7f06 /* sqrt(0.2462120056152344) ~=0.4961853027343750*/, 
  0x8007 /* sqrt(0.2501182556152344) ~=0.5001068115234375*/,   0x8106 /* sqrt(0.2540245056152344) ~=0.5039978027343750*/, 
  0x8203 /* sqrt(0.2579307556152344) ~=0.5078582763671875*/,   0x82fe /* sqrt(0.2618370056152344) ~=0.5116882324218750*/, 
  0x83f8 /* sqrt(0.2657432556152344) ~=0.5155029296875000*/,   0x84ef /* sqrt(0.2696495056152344) ~=0.5192718505859375*/, 
  0x85e5 /* sqrt(0.2735557556152344) ~=0.5230255126953125*/,   0x86d8 /* sqrt(0.2774620056152344) ~=0.5267333984375000*/, 
  0x87cb /* sqrt(0.2813682556152344) ~=0.5304412841796875*/,   0x88bb /* sqrt(0.2852745056152344) ~=0.5341033935546875*/, 
  0x89aa /* sqrt(0.2891807556152344) ~=0.5377502441406250*/,   0x8a97 /* sqrt(0.2930870056152344) ~=0.5413665771484375*/, 
  0x8b83 /* sqrt(0.2969932556152344) ~=0.5449676513671875*/,   0x8c6d /* sqrt(0.3008995056152344) ~=0.5485382080078125*/, 
  0x8d55 /* sqrt(0.3048057556152344) ~=0.5520782470703125*/,   0x8e3d /* sqrt(0.3087120056152344) ~=0.5556182861328125*/, 
  0x8f22 /* sqrt(0.3126182556152344) ~=0.5591125488281250*/,   0x9006 /* sqrt(0.3165245056152344) ~=0.5625915527343750*/, 
  0x90e9 /* sqrt(0.3204307556152344) ~=0.5660552978515625*/,   0x91cb /* sqrt(0.3243370056152344) ~=0.5695037841796875*/, 
  0x92ab /* sqrt(0.3282432556152344) ~=0.5729217529296875*/,   0x938a /* sqrt(0.3321495056152344) ~=0.5763244628906250*/, 
  0x9467 /* sqrt(0.3360557556152344) ~=0.5796966552734375*/,   0x9543 /* sqrt(0.3399620056152344) ~=0.5830535888671875*/, 
  0x961e /* sqrt(0.3438682556152344) ~=0.5863952636718750*/,   0x96f8 /* sqrt(0.3477745056152344) ~=0.5897216796875000*/, 
  0x97d0 /* sqrt(0.3516807556152344) ~=0.5930175781250000*/,   0x98a7 /* sqrt(0.3555870056152344) ~=0.5962982177734375*/, 
  0x997d /* sqrt(0.3594932556152344) ~=0.5995635986328125*/,   0x9a52 /* sqrt(0.3633995056152344) ~=0.6028137207031250*/, 
  0x9b26 /* sqrt(0.3673057556152344) ~=0.6060485839843750*/,   0x9bf9 /* sqrt(0.3712120056152344) ~=0.6092681884765625*/, 
  0x9cca /* sqrt(0.3751182556152344) ~=0.6124572753906250*/,   0x9d9b /* sqrt(0.3790245056152344) ~=0.6156463623046875*/, 
  0x9e6a /* sqrt(0.3829307556152344) ~=0.6188049316406250*/,   0x9f38 /* sqrt(0.3868370056152344) ~=0.6219482421875000*/, 
  0xa006 /* sqrt(0.3907432556152344) ~=0.6250915527343750*/,   0xa0d2 /* sqrt(0.3946495056152344) ~=0.6282043457031250*/, 
  0xa19d /* sqrt(0.3985557556152344) ~=0.6313018798828125*/,   0xa268 /* sqrt(0.4024620056152344) ~=0.6343994140625000*/, 
  0xa331 /* sqrt(0.4063682556152344) ~=0.6374664306640625*/,   0xa3f9 /* sqrt(0.4102745056152344) ~=0.6405181884765625*/, 
  0xa4c0 /* sqrt(0.4141807556152344) ~=0.6435546875000000*/,   0xa587 /* sqrt(0.4180870056152344) ~=0.6465911865234375*/, 
  0xa64c /* sqrt(0.4219932556152344) ~=0.6495971679687500*/,   0xa711 /* sqrt(0.4258995056152344) ~=0.6526031494140625*/, 
  0xa7d5 /* sqrt(0.4298057556152344) ~=0.6555938720703125*/,   0xa897 /* sqrt(0.4337120056152344) ~=0.6585540771484375*/, 
  0xa959 /* sqrt(0.4376182556152344) ~=0.6615142822265625*/,   0xaa1a /* sqrt(0.4415245056152344) ~=0.6644592285156250*/, 
  0xaadb /* sqrt(0.4454307556152344) ~=0.6674041748046875*/,   0xab9a /* sqrt(0.4493370056152344) ~=0.6703186035156250*/, 
  0xac59 /* sqrt(0.4532432556152344) ~=0.6732330322265625*/,   0xad16 /* sqrt(0.4571495056152344) ~=0.6761169433593750*/, 
  0xadd3 /* sqrt(0.4610557556152344) ~=0.6790008544921875*/,   0xae8f /* sqrt(0.4649620056152344) ~=0.6818695068359375*/, 
  0xaf4b /* sqrt(0.4688682556152344) ~=0.6847381591796875*/,   0xb005 /* sqrt(0.4727745056152344) ~=0.6875762939453125*/, 
  0xb0bf /* sqrt(0.4766807556152344) ~=0.6904144287109375*/,   0xb178 /* sqrt(0.4805870056152344) ~=0.6932373046875000*/, 
  0xb230 /* sqrt(0.4844932556152344) ~=0.6960449218750000*/,   0xb2e8 /* sqrt(0.4883995056152344) ~=0.6988525390625000*/, 
  0xb39f /* sqrt(0.4923057556152344) ~=0.7016448974609375*/,   0xb455 /* sqrt(0.4962120056152344) ~=0.7044219970703125*/, 
  0xb50a /* sqrt(0.5001182556152344) ~=0.7071838378906250*/,   0xb5bf /* sqrt(0.5040245056152344) ~=0.7099456787109375*/, 
  0xb673 /* sqrt(0.5079307556152344) ~=0.7126922607421875*/,   0xb726 /* sqrt(0.5118370056152344) ~=0.7154235839843750*/, 
  0xb7d8 /* sqrt(0.5157432556152344) ~=0.7181396484375000*/,   0xb88a /* sqrt(0.5196495056152344) ~=0.7208557128906250*/, 
  0xb93c /* sqrt(0.5235557556152344) ~=0.7235717773437500*/,   0xb9ec /* sqrt(0.5274620056152344) ~=0.7262573242187500*/, 
  0xba9c /* sqrt(0.5313682556152344) ~=0.7289428710937500*/,   0xbb4b /* sqrt(0.5352745056152344) ~=0.7316131591796875*/, 
  0xbbfa /* sqrt(0.5391807556152344) ~=0.7342834472656250*/,   0xbca8 /* sqrt(0.5430870056152344) ~=0.7369384765625000*/, 
  0xbd55 /* sqrt(0.5469932556152344) ~=0.7395782470703125*/,   0xbe02 /* sqrt(0.5508995056152344) ~=0.7422180175781250*/, 
  0xbeae /* sqrt(0.5548057556152344) ~=0.7448425292968750*/,   0xbf5a /* sqrt(0.5587120056152344) ~=0.7474670410156250*/, 
  0xc005 /* sqrt(0.5626182556152344) ~=0.7500762939453125*/,   0xc0af /* sqrt(0.5665245056152344) ~=0.7526702880859375*/, 
  0xc159 /* sqrt(0.5704307556152344) ~=0.7552642822265625*/,   0xc202 /* sqrt(0.5743370056152344) ~=0.7578430175781250*/, 
  0xc2ab /* sqrt(0.5782432556152344) ~=0.7604217529296875*/,   0xc353 /* sqrt(0.5821495056152344) ~=0.7629852294921875*/, 
  0xc3fa /* sqrt(0.5860557556152344) ~=0.7655334472656250*/,   0xc4a1 /* sqrt(0.5899620056152344) ~=0.7680816650390625*/, 
  0xc547 /* sqrt(0.5938682556152344) ~=0.7706146240234375*/,   0xc5ed /* sqrt(0.5977745056152344) ~=0.7731475830078125*/, 
  0xc693 /* sqrt(0.6016807556152344) ~=0.7756805419921875*/,   0xc737 /* sqrt(0.6055870056152344) ~=0.7781829833984375*/, 
  0xc7dc /* sqrt(0.6094932556152344) ~=0.7807006835937500*/,   0xc87f /* sqrt(0.6133995056152344) ~=0.7831878662109375*/, 
  0xc922 /* sqrt(0.6173057556152344) ~=0.7856750488281250*/,   0xc9c5 /* sqrt(0.6212120056152344) ~=0.7881622314453125*/, 
  0xca67 /* sqrt(0.6251182556152344) ~=0.7906341552734375*/,   0xcb09 /* sqrt(0.6290245056152344) ~=0.7931060791015625*/, 
  0xcbaa /* sqrt(0.6329307556152344) ~=0.7955627441406250*/,   0xcc4b /* sqrt(0.6368370056152344) ~=0.7980194091796875*/, 
  0xcceb /* sqrt(0.6407432556152344) ~=0.8004608154296875*/,   0xcd8a /* sqrt(0.6446495056152344) ~=0.8028869628906250*/, 
  0xce2a /* sqrt(0.6485557556152344) ~=0.8053283691406250*/,   0xcec8 /* sqrt(0.6524620056152344) ~=0.8077392578125000*/, 
  0xcf67 /* sqrt(0.6563682556152344) ~=0.8101654052734375*/,   0xd004 /* sqrt(0.6602745056152344) ~=0.8125610351562500*/, 
  0xd0a2 /* sqrt(0.6641807556152344) ~=0.8149719238281250*/,   0xd13e /* sqrt(0.6680870056152344) ~=0.8173522949218750*/, 
  0xd1db /* sqrt(0.6719932556152344) ~=0.8197479248046875*/,   0xd277 /* sqrt(0.6758995056152344) ~=0.8221282958984375*/, 
  0xd312 /* sqrt(0.6798057556152344) ~=0.8244934082031250*/,   0xd3ad /* sqrt(0.6837120056152344) ~=0.8268585205078125*/, 
  0xd448 /* sqrt(0.6876182556152344) ~=0.8292236328125000*/,   0xd4e2 /* sqrt(0.6915245056152344) ~=0.8315734863281250*/, 
  0xd57c /* sqrt(0.6954307556152344) ~=0.8339233398437500*/,   0xd615 /* sqrt(0.6993370056152344) ~=0.8362579345703125*/, 
  0xd6ae /* sqrt(0.7032432556152344) ~=0.8385925292968750*/,   0xd746 /* sqrt(0.7071495056152344) ~=0.8409118652343750*/, 
  0xd7de /* sqrt(0.7110557556152344) ~=0.8432312011718750*/,   0xd876 /* sqrt(0.7149620056152344) ~=0.8455505371093750*/, 
  0xd90d /* sqrt(0.7188682556152344) ~=0.8478546142578125*/,   0xd9a4 /* sqrt(0.7227745056152344) ~=0.8501586914062500*/, 
  0xda3a /* sqrt(0.7266807556152344) ~=0.8524475097656250*/,   0xdad0 /* sqrt(0.7305870056152344) ~=0.8547363281250000*/, 
  0xdb66 /* sqrt(0.7344932556152344) ~=0.8570251464843750*/,   0xdbfb /* sqrt(0.7383995056152344) ~=0.8592987060546875*/, 
  0xdc90 /* sqrt(0.7423057556152344) ~=0.8615722656250000*/,   0xdd24 /* sqrt(0.7462120056152344) ~=0.8638305664062500*/, 
  0xddb8 /* sqrt(0.7501182556152344) ~=0.8660888671875000*/,   0xde4b /* sqrt(0.7540245056152344) ~=0.8683319091796875*/, 
  0xdedf /* sqrt(0.7579307556152344) ~=0.8705902099609375*/,   0xdf72 /* sqrt(0.7618370056152344) ~=0.8728332519531250*/, 
  0xe004 /* sqrt(0.7657432556152344) ~=0.8750610351562500*/,   0xe096 /* sqrt(0.7696495056152344) ~=0.8772888183593750*/, 
  0xe128 /* sqrt(0.7735557556152344) ~=0.8795166015625000*/,   0xe1b9 /* sqrt(0.7774620056152344) ~=0.8817291259765625*/, 
  0xe24a /* sqrt(0.7813682556152344) ~=0.8839416503906250*/,   0xe2db /* sqrt(0.7852745056152344) ~=0.8861541748046875*/, 
  0xe36b /* sqrt(0.7891807556152344) ~=0.8883514404296875*/,   0xe3fb /* sqrt(0.7930870056152344) ~=0.8905487060546875*/, 
  0xe48a /* sqrt(0.7969932556152344) ~=0.8927307128906250*/,   0xe51a /* sqrt(0.8008995056152344) ~=0.8949279785156250*/, 
  0xe5a9 /* sqrt(0.8048057556152344) ~=0.8971099853515625*/,   0xe637 /* sqrt(0.8087120056152344) ~=0.8992767333984375*/, 
  0xe6c5 /* sqrt(0.8126182556152344) ~=0.9014434814453125*/,   0xe753 /* sqrt(0.8165245056152344) ~=0.9036102294921875*/, 
  0xe7e1 /* sqrt(0.8204307556152344) ~=0.9057769775390625*/,   0xe86e /* sqrt(0.8243370056152344) ~=0.9079284667968750*/, 
  0xe8fa /* sqrt(0.8282432556152344) ~=0.9100646972656250*/,   0xe987 /* sqrt(0.8321495056152344) ~=0.9122161865234375*/, 
  0xea13 /* sqrt(0.8360557556152344) ~=0.9143524169921875*/,   0xea9f /* sqrt(0.8399620056152344) ~=0.9164886474609375*/, 
  0xeb2a /* sqrt(0.8438682556152344) ~=0.9186096191406250*/,   0xebb6 /* sqrt(0.8477745056152344) ~=0.9207458496093750*/, 
  0xec40 /* sqrt(0.8516807556152344) ~=0.9228515625000000*/,   0xeccb /* sqrt(0.8555870056152344) ~=0.9249725341796875*/, 
  0xed55 /* sqrt(0.8594932556152344) ~=0.9270782470703125*/,   0xeddf /* sqrt(0.8633995056152344) ~=0.9291839599609375*/, 
  0xee69 /* sqrt(0.8673057556152344) ~=0.9312896728515625*/,   0xeef2 /* sqrt(0.8712120056152344) ~=0.9333801269531250*/, 
  0xef7b /* sqrt(0.8751182556152344) ~=0.9354705810546875*/,   0xf004 /* sqrt(0.8790245056152344) ~=0.9375610351562500*/, 
  0xf08c /* sqrt(0.8829307556152344) ~=0.9396362304687500*/,   0xf114 /* sqrt(0.8868370056152344) ~=0.9417114257812500*/, 
  0xf19c /* sqrt(0.8907432556152344) ~=0.9437866210937500*/,   0xf223 /* sqrt(0.8946495056152344) ~=0.9458465576171875*/, 
  0xf2ab /* sqrt(0.8985557556152344) ~=0.9479217529296875*/,   0xf331 /* sqrt(0.9024620056152344) ~=0.9499664306640625*/, 
  0xf3b8 /* sqrt(0.9063682556152344) ~=0.9520263671875000*/,   0xf43e /* sqrt(0.9102745056152344) ~=0.9540710449218750*/, 
  0xf4c4 /* sqrt(0.9141807556152344) ~=0.9561157226562500*/,   0xf54a /* sqrt(0.9180870056152344) ~=0.9581604003906250*/, 
  0xf5d0 /* sqrt(0.9219932556152344) ~=0.9602050781250000*/,   0xf655 /* sqrt(0.9258995056152344) ~=0.9622344970703125*/, 
  0xf6da /* sqrt(0.9298057556152344) ~=0.9642639160156250*/,   0xf75e /* sqrt(0.9337120056152344) ~=0.9662780761718750*/, 
  0xf7e3 /* sqrt(0.9376182556152344) ~=0.9683074951171875*/,   0xf867 /* sqrt(0.9415245056152344) ~=0.9703216552734375*/, 
  0xf8ea /* sqrt(0.9454307556152344) ~=0.9723205566406250*/,   0xf96e /* sqrt(0.9493370056152344) ~=0.9743347167968750*/, 
  0xf9f1 /* sqrt(0.9532432556152344) ~=0.9763336181640625*/,   0xfa74 /* sqrt(0.9571495056152344) ~=0.9783325195312500*/, 
  0xfaf7 /* sqrt(0.9610557556152344) ~=0.9803314208984375*/,   0xfb79 /* sqrt(0.9649620056152344) ~=0.9823150634765625*/, 
  0xfbfb /* sqrt(0.9688682556152344) ~=0.9842987060546875*/,   0xfc7d /* sqrt(0.9727745056152344) ~=0.9862823486328125*/, 
  0xfcff /* sqrt(0.9766807556152344) ~=0.9882659912109375*/,   0xfd80 /* sqrt(0.9805870056152344) ~=0.9902343750000000*/, 
  0xfe01 /* sqrt(0.9844932556152344) ~=0.9922027587890625*/,   0xfe82 /* sqrt(0.9883995056152344) ~=0.9941711425781250*/, 
  0xff03 /* sqrt(0.9923057556152344) ~=0.9961395263671875*/,   0xff83 /* sqrt(0.9962120056152344) ~=0.9980926513671875*/
};

uint16_t square_root_tab( uint8_t index ) noexcept
  {
  return square_root_table__[index];
  }
}
