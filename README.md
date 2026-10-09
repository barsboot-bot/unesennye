# UNESENNYE MUSIC SYSTEM v1.2.4 — Client Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.4  
**Requires server:** `@unesennye_servermod`

## Fixes in 1.2.4
- SD card items only here (no duplicate on server)
- Full `attachments[]` override instead of unreliable `+=`
- Real SoundSet playback via SEffectManager
- Handshake uses CallQueue; disconnect delayed so dialog can show
- RADIO_BROADCAST reads Param3&lt;playlistId, track, soundSet&gt;
- Removed fragile DZ_Radio requiredAddon

## Launch (client)
```
-mod=@unesennye;@unesennye_music_db
```

**Author:** KRa Tos (Константин)
