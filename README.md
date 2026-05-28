# DirectXの授業

## Preview
!["img"](https://github.com/RiruOwO/DirectXTK12/blob/master/HuGame%20(DX12_sRGB).png)

>  [!NOTE]
>  assetsに画像を置く<br>
>  DescripterHeapやspriteを書く<br>

>  [!TIP]  
>  画像分 ```descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 3);``` を変える <br>
>  画像分 private関数に定義する<br>

# 5/14<br>

## エマちゃんを移動させた<br>
>  [!NOTE]
>  座標用の変数を宣言する  `float player_x_, player_y_;`<br>
>  Initialize関数に初期値を設定する <br>
>  Update関数に移動させるのを書く  <br>
>  Render関数に変数を用いる  <br>

>  [!TIP]
>  player_postion_x_と長いのが嫌な時は宣言時にplayer_x_など短くすることができる
