# UNESENNYE CLIENT v1.3.1

**Автор:** KRa Tos (Константин)

Клиентский мод системы музыки Unesennye.

**Требует серверный мод** `@unesennye_servermod` (иначе handshake отключит игрока).

## GUI меню музыки

Layout: `gui/layouts/unesennye_music.layout`

### Как открыть в игре

Посмотрите на рацию или машину со слотом SD → действие **Open Unesennye Music**.

### Управление в меню

- список треков (выбор / двойной клик — воспроизведение)
- **Play** — играть
- **Stop** — остановить
- **Prev** / **Next** — предыдущий / следующий трек
- **X** — закрыть

## Предметы

- `Unesennye_SD_Card` / `Unesennye_SD_Card_Empty` — SD-карта
- `Unesennye_Cassette` — кассета
- `Unesennye_Disk` — диск

Quantity на карте = ID плейлиста.

## Действия

- Вставить носитель
- Извлечь носитель
- Воспроизвести / остановить
- Открыть меню музыки

## Запуск (клиент)

```
-mod=@unesennye;@unesennye_music_db
```

**Автор:** KRa Tos (Константин)
