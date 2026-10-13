1.Struktur invariant adalah bagian-bagian yang konsep dan aturannya tidak berubah sepanjang permainan berjalan, apa pun kartu yang keluar atau berapa pun skor yang didapat.
Jumlah kartu per tangan selalu 5. Mau di round berapa pun, HandGenerator selalu mengambil 5 kartu dari deck. Ini tidak pernah berubah.

Deck selalu berisi 52 kartu (13 rank × 4 suit). Setiap kali generateHand() dipanggil, deck dibentuk ulang dengan komposisi yang sama.

Urutan pengecekan kombinasi selalu dari tertinggi ke terendah. StraightFlushChecker selalu dicek pertama, lalu FourOfAKindChecker, FullHouseChecker, FlushChecker, StraightChecker, ThreeOfAKindChecker, TwoPairChecker, PairChecker, dan terakhir HighCardChecker. Rantai ini tetap.

Aturan penilaian skor per kombinasi tetap. Straight Flush = 100, Four of a Kind = 80, dan seterusnya. Tidak berubah selama permainan.

Target blind tetap 30. Di BlindRule, nilai targetScore = 30 tidak berubah.

Jumlah round tetap 3. Loop di GameManager::runSession() selalu berjalan dari round 1 sampai 3.

Alur tiap round tetap: generate hand → score hand → check blind → earn money. Urutan ini tidak pernah dibalik.

Struktur data Card, Hand, dan enum Suit, Rank, HandRank tidak berubah isinya.

2.Bagian mutable adalah semua yang nilainya berubah selama program berjalan atau berbeda tiap kali program dijalankan.

Isi kartu di tangan pemain. Setiap panggilan generateHand() menghasilkan 5 kartu yang berbeda karena deck di-shuffle dengan std::mt19937 yang di-seed dari std::random_device.

Urutan kartu di dalam deck setelah di-shuffle. Deck yang awalnya terurut (2H, 3H, ..., AS) menjadi acak.

playerMoney di GameManager. Nilainya bertambah setiap kali pemain menang blind. Awalnya 0, bisa jadi 8, 13, 32, dan seterusnya.

Hasil deteksi HandRank. Tergantung kartu yang keluar, bisa High Card, Pair, Straight, Flush, dan lain-lain.

Skor (baseScore) yang dihitung ScoringRule. Berubah sesuai kombinasi yang terdeteksi.

Status menang/kalah (isWin) di BlindRule. Bisa true atau false tergantung skor.

Uang yang didapat (moneyEarned) di RewardRule. Nol kalau kalah, atau 5 + score/10 kalau menang.

Pointer nextChecker secara teknis bisa diubah kapan saja lewat setNext(), meskipun dalam praktiknya di-set sekali di awal scoreHand().

Round counter di loop for (int round = 1; round <= 3; ++round) — nilainya bertambah tiap iterasi.

3.Kalau fiturnya soal aturan permainan (skor, blind, reward), hampir selalu berubah di game_rules.h. Kalau fiturnya soal alur/orkestrasi, berubah di game_manager.h.

4.Kalau scoringRule.scoreHand() dipanggil setelah blindRule.checkBlind(), hal yang sama terjadi: blind tidak punya data skor.

Kalau earnMoney() dipanggil sebelum checkBlind(), maka isWin belum diketahui → parameter win tidak valid.

Kalau loop round dihapus dan hanya dijalankan sekali, maka fitur "3 round" hilang, dan playerMoney hanya terakumulasi dari 1 round.

Kalau loop round dibalik urutannya (dari round 3 ke round 1), secara logika tidak ada yang rusak karena tiap round independen — tapi secara naratif jadi aneh (round 3 dulu, baru round 1).
