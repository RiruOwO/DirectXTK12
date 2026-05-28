# DirectXの授業

## Preview
!["img"](https://github.com/RiruOwO/DirectXTK12/blob/master/2026_05_14.png)

>  [!NOTE]
>  assetsに画像を置く<br>
>  DescripterHeapやspriteを書く<br>

>  [!TIP]  
>  画像分 ```descriptor_heap_ = DirectXTK::CreateDescriptorHeap(device, 3);``` を変える <br>
>  画像分 private関数に定義する<br>

# 5/14 | エマちゃんを横に移動させた


>  [!NOTE]
>  座標用の変数を宣言する  `float player_x_, player_y_;`<br>
>  Initialize関数に初期値を設定する <br>
>  Update関数に移動させるのを書く  <br>
>  Render関数に変数を用いる  <br>

>  [!TIP]
>  player_postion_x_と長いのが嫌な時は宣言時にplayer_x_など短くすることができる <br>

# 5/28 | シオンちゃんをキーボード入力で左右移動させた <br>

#### こんにちワッフル...
!["img"](https://github.com/RiruOwO/DirectXTK12/blob/master/2026_05_28.png)

>  [!NOTE]
> ### 移動処理
> DXTKはキーボードの状態が毎フレームUpdate関数で取得され、その状態を参照して移動処理を行っている <br>
> 押されている <br>
> 押された瞬間 <br>
> 離された瞬間 <br>
> 上記3つがDXTKにはある <br>
> <br>
> ### 画面外に行かない処理 <br>

> [!TIP]
> DXTKのgithubにkeycodeがある <br>
> 画面外に行かない処理の std::max は渡された2つの値のうち、大きい方の値を返す / std::min は小さい方の値を返す<br>
> ① プレイヤーが画面内にいるとき（例: x = 50.0f）<br>
>   std::max(50.0f, 0.0f) が実行される <br>
>   50 と 0 を比べたら 50 の方が大きいので 50 が返される <br>
>   結果 player_pos_.x は 50.0f のまま <br>
> ② プレイヤーが左にハミ出そうとしたとき（例: x = -10.0f）<br>
>   std::max(-10.0f, 0.0f) が実行される <br>
>   -10 と 0 を比べたら 0 の方が大きいので 0 が返される <br>
>   結果 player_pos_.x に 0.0f が強制上書きされる <br>

