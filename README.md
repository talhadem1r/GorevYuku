# Roket Görev Yükü Yazılımı

ATÜ-EBC Bürküt Roket Takımı'nın **TEKNOFEST 2025 Roket Yarışması – Orta İrtifa** kategorisi için geliştirdiği görev yükü yazılımı. Görev yükü, roketten ayrıldıktan sonra çevresel ve konum verilerini toplayıp LoRa ile yer istasyonuna iletir.

## Özellikler
- BMP180 ile sıcaklık ve basınç (hPa) ölçümü
- GPS ile enlem, boylam ve irtifa takibi
- LoRa E22 ile ~200 ms aralıkla veri gönderimi
- Uçuş bilgisayarından ayrı LoRa adresi sayesinde iki sistemin verisi yer istasyonunda ayrıştırılır

## Donanım ve Bağlantılar
| Bileşen | Bağlantı |
|---|---|
| [Arduino kart modeli] | Ana kontrolcü |
| BMP180 (sıcaklık/basınç) | I2C |
| GPS modülü | SoftwareSerial – D6 / D5 |
| Ebyte E22 LoRa | SoftwareSerial – D9 / D8 |

## Veri Paketi
GPS irtifası, enlem, boylam, basınç ve sıcaklık tek bir `struct` olarak LoRa üzerinden gönderilir.

## Kullanılan Kütüphaneler
Adafruit BMP085 Unified · Adafruit Unified Sensor · EByte LoRa E22 · TinyGPS++ · SimpleKalmanFilter

## Takımdaki Rolüm
[Örn: Görev yükü yazılımının geliştirilmesi ve LoRa haberleşmesi]

> Uçuş kontrol bilgisayarı yazılımı: [RoketGondericiKod](https://github.com/talhadem1r/RoketGondericiKod)
