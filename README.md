# Açıklama

Bu kütüphane Arduino ile OCMJ4X8B-2 LCD ekran kullanımı için yazılmıştır. OCMJ4X8B-2 128x64 karaktere sahip bir LCD modüldür.
Arduino ile kullanılan standart 128x64 karakter LCD ler farklı yapıya ve pin dizilişine sahiptir. Bu sebeple u8glib veya glcd
gibi kütüphanlerle sürülemezler. Bu sebeple bu kütüphaneyi yazma ihtiyacı duyulmuştur.

<img src="https://img.alicdn.com/imgextra/i3/737283681/TB2lLOKv79WBuNjSspeXXaz5VXa_!!737283681.jpg" height="300px"> <img src="https://img.alicdn.com/imgextra/i2/737283681/TB2Qg9Kv1OSBuNjy0FdXXbDnVXa_!!737283681.jpg" height="300px">

Datasheet'e burdan ulaşabilirsiniz;
<a href="www.hebangdianzi.com/upload/yj/ex_Bxl.rar">www.hebangdianzi.com/upload/yj/ex_Bxl.rar</a>

Pinler hakkında detaylı bilgiye buradan ulaşabilirsiniz;
<a href="www.hebangdianzi.com/upload/yj/OCMJ4X8B-2.rar">www.hebangdianzi.com/upload/yj/OCMJ4X8B-2.rar</a>

# Pin Yapısı

Modül 18 pine sahiptir. Bunlar;<br>
<ul style="float:left">
<li>1 - Backlight(-)</li>
<li>2 - Backlight(+)</li>
<li>3 - Vss</li>
<li>4 - Vcc</li>
<li>5 - D0</li>
<li>6 - D1</li>
<li>7 - D2</li>
<li>8 - D3</li>
<li>9 - D4</li>
<li>10 - D5</li>
<li>11 - D6</li>
<li>12 - D7</li>
<li>13 - BUSY</li>
<li>14 - REQ</li>
<li>15 - RESET</li>
<li>16 - NC</li>
<li>17 - RT</li>
<li>18 - RT</li>
</ul>

<div style="float:right">
1-2   : Ekran aydınlatması için<br>
3-4   : Modül beslemesi (Vcc:+5V, Vss:GND)<br>
5-12  : Veri hattı (8bit)<br>
13-14 : Veri yazma/meşguliyet hattı<br>
15    : Modül resetleme hattı<br>
16    : Bağlantı gerekmez (Boş)<br>
17-18 : Karakter kontrast ayarı (isteğe bağlı kullanım)<br>
</div>


# Kütüphane Kurulumu

İndirdiğiniz OCMJ4X8B klasörünü Arduino Ide nin kurulu olduğu yerde "Libraries" klasörü içerisine veya Belgeler/Arduino/Libraries klasörü içerisine kopyalayarak kurulumu tamamlayabilirsiniz. 
Klasörü .zip olarak indirirseniz IDE üzerinden "Taslak>Library Yükle>.ZIP Kitaplığı Yükle" sekmelerinden de yükleme işlemini gerçekleştirebilirsiniz.


# Bağlantı Şeması

<a href="https://hizliresim.com/yj8dBj"><img src="https://i.hizliresim.com/yj8dBj.png"></a><br>

Şemada bulunan potansiyometrenin değeri 10kΩ dur ve bağlanması isteğe bağlıdır. Bu potansiyometre ile karakterlerin kontrastını ayarlayabilirsiniz.


# Test

Kütüphane kurulumunu ve bağlantıyı gerçekleştirdiyseniz, "OCMJ4X8B/examples/OCMJ4X8B-Test/OCMJ4X8B-Test.ino" yu veya IDE üzerinden "Dosya>Örnekler>OCMJ4X8B>OCMJ4X8B-Test" sekmelerinden örnek programı Arduino ya upload ederek modülü test edebilirsiniz.<br>
Örnek program çıktısı:

<a href="https://hizliresim.com/WoAWW4"><img src="https://i.hizliresim.com/WoAWW4.jpg"></a>
