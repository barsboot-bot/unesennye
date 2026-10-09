# Текстуры предметов Unesennye

**Автор:** KRa Tos (Константин)

## Предметы

| Текстура | Предмет |
|----------|--------|
| `sd_card_co.paa` | SD-карта с музыкой |
| `sd_card_empty_co.paa` | Пустая SD-карта |
| `cassette_co.paa` | Кассета |
| `disk_co.paa` | Диск |

## Как получить .paa

### Вариант A — генератор (Python + Pillow)

```bat
pip install Pillow
python tools\generate_item_textures.py
```

Появятся `.png` и `.tga` в этой папке.

### Вариант B — встроенные PNG

```bat
python tools\install_textures.py
```

### Конвертация в PAA (обязательно для игры)

1. Откройте **DayZ Tools → TexView2**
2. File → Open → каждый `.png` или `.tga`
3. File → Save As → тип **PAA**
4. Имена должны быть:
   - `sd_card_co.paa`
   - `sd_card_empty_co.paa`
   - `cassette_co.paa`
   - `disk_co.paa`
5. Сохраните в `data/textures/`
6. Упакуйте мод в PBO

Без `.paa` предметы могут отображаться розовыми/белыми.
