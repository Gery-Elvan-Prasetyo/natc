
# Feature Inventory

Daftar fitur yang akan dipelajari dan direncanakan untuk Serpantinum Native.

Status:
- [ ] Belum dianalisis
- [ ] Sudah dianalisis
- [ ] Sedang dikembangkan
- [ ] Selesai dan

## 1. Desktop Bar
- [ ] Jam dan tanggal
- [ ] Indikator workspace Hyprland
- [ ] Informasi jendela aktif
- [ ] Status jaringan
- [ ] Status baterai
- [ ] Kontrol volume
- [ ] Kontrol brightness

## 2. Launcher dan Navigasi
- [ ] Launcher aplikasi
- [ ] Pencarian aplikasi
- [ ] Pintasan keyboard

## 3. Control Center
- [ ] Pengaturan audio
- [ ] Pengaturan jaringan
- [ ] Pengaturan tampilan
- [ ] Pengaturan daya

## 4. Notifikasi
- [ ] Tampilan notifikasi
- [ ] Riwayat notifikasi
- [ ] Kontrol notifikasi

## 5. Tampilan Desktop
- [ ] Wallpaper
- [ ] Tema dan warna
- [ ] Transparansi
- [ ] Animasi
- [ ] Pengaturan panel

## 6. Fitur Tambahan
- [ ] Clipboard
- [ ] Screenshot
- [ ] Pengaturan shell
- [ ] Konfigurasi pengguna

## 7. Target Teknis
- [ ] Integrasi dengan Hyprland
- [ ] Dukungan Wayland layer-shell
- [ ] Penggunaan RAM dan CPU terukur
- [ ] Pemulihan setelah shell crash
- [ ] Pengaturan tidak hilang setelah restart

## Catatan
Daftar ini masih berupa rancangan awal.
Fitur final harus dibandingkan dengan repositori
Serpantinum asli sebelum implementasi.


## Audit Fitur Serpantinum Upstream

Status:
- [ ] Belum diaudit seluruhnya
- [ ] Sudah dicocokkan dengan dokumentasi resmi
- [ ] Sudah diperiksa terhadap implementasi upstream

### 1. Desktop Shell
- [ ] Status bar modular
- [ ] Workspace indicators
- [ ] Jam, tanggal, dan kalender
- [ ] System tray
- [ ] Informasi media dan kontrol pemutaran
- [ ] Monitor CPU, RAM, suhu, dan disk
- [ ] Launcher aplikasi
- [ ] Dock aplikasi
- [ ] Panel jaringan dan audio
- [ ] Clipboard history
- [ ] Pusat notifikasi dan riwayatnya
- [ ] OSD
- [ ] Wallpaper picker dan preview
- [ ] Pengaturan tema dan warna dinamis
- [ ] Kontrol daya dan pengelolaan kondisi idle
- [ ] Screenshot overlay
- [ ] Widget desktop dan editor widget
- [ ] Antarmuka layar kunci

### 2. Konfigurasi dan Integrasi
- [ ] Pengaturan dapat diubah tanpa restart penuh
- [ ] Konfigurasi tampilan dan posisi komponen
- [ ] Dukungan HiDPI dan multi-monitor
- [ ] Integrasi IPC compositor
- [ ] Pengaturan dan dokumentasi keybind
- [ ] Logging dan diagnostik
- [ ] Penanganan error dan pemulihan komponen

### 3. Aturan Proyek Native
- [ ] Ukur penggunaan RAM dan CPU tiap modul
- [ ] Hindari polling yang tidak diperlukan
- [ ] Komponen yang tidak digunakan tidak perlu aktif
- [ ] Semua fitur memiliki pengujian dasar
- [ ] Tidak mengubah konfigurasi Hyprland pengguna secara diam-diam
- [ ] Bandingkan performa pada kondisi penggunaan yang setara

Catatan:
Daftar ini merupakan inventaris awal dari dokumentasi upstream,
bukan konfirmasi bahwa setiap fitur sudah diaudit pada kode sumber.
Prioritas dan teknologi implementasi belum diputuskan.

