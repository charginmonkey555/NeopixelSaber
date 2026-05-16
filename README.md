# NeoPixel Lightsaber

A budget-friendly NeoPixel lightsaber upgrade using an Arduino Nano, DFPlayer Mini, and WS2812B LED strips. This project replaces the internals of a cheap baselit saber with a fully addressable blade and sound effects. I am building this project because I wanted a bright, sound‑enabled lightsaber on a budget. I also wanted to learn more about embedded electronics, LED animation, and CAD design.

## Bill of Materials

| Item | Qty | Price | Notes | Link |
|------|-----|--------|--------|------|
| WS2812B LED Strip (144/m) | 4 | £0 | Blade lighting | [link](https://www.aliexpress.com/item/1005006361248733.html?spm=a2g0o.cart.0.0.589338daFfDbAB&mp=1&pdp_npi=6%40dis%21GBP%21GBP%208.47%21GBP%205.59%21%21GBP%205.59%21%21%21%40211b80c217710243391906147efbd4%2112000036893365738%21ct%21UK%216184487227%21%214%210%21) |
| Arduino Nano | 1 | £0 | Main controller | [link](https://www.aliexpress.com/item/1005007475356474.html?spm=a2g0o.detail.0.0.7311NpQdNpQdet&mp=1&pdp_npi=6%40dis%21GBP%21GBP%201.91%21GBP%201.89%21%21GBP%201.89%21%21%21%40211b80c217710243987167114efbd4%2112000040904856242%21ct%21UK%216184487227%21%211%210%21) |
| DFPlayer Mini | 1 | £0 | Sound module | [link](https://www.aliexpress.com/item/1005006573885252.html?spm=a2g0o.detail.0.0.48568kc18kc1Il&mp=1&pdp_npi=6%40dis%21GBP%21GBP%202.61%21GBP%201.30%21%21GBP%201.30%21%21%21%40211b80c217710244296917643efbd4%2112000037708194412%21ct%21UK%216184487227%21%211%210%21) |
| 8Ω 2W Speaker | 1 | £0 | Audio output | [link](https://www.aliexpress.com/item/1005007471900641.html?spm=a2g0o.detail.0.0.7d82WXXIWXXIGG&mp=1&pdp_npi=6%40dis%21GBP%21GBP%202.25%21GBP%202.07%21%21GBP%202.07%21%21%21%40211b80c217710244649128269efbd4%2112000040893974006%21ct%21UK%216184487227%21%211%210%21) |
| 18650 Battery (3500mAh) | 1 | £0 | Power source | [link](https://www.aliexpress.com/item/1005008772657403.html?spm=a2g0o.cart.0.0.bf7438daXQ1Fxc&mp=1&pdp_npi=6%40dis%21GBP%21GBP%2010.08%21GBP%205.54%21%21GBP%205.54%21%21%21%40211b80c217710245061978829efbd4%2112000046612536359%21ct%21UK%216184487227%21%211%210%21&pdp_ext_f=%7B"cart2PdpParams"%3A%7B"pdpBusinessMode"%3A"retail"%7D%7D) |
| TP4056 USB‑C Charger | 1 | £0 | Battery charging | [link](https://www.aliexpress.com/item/1005008221413637.html?spm=a2g0o.productlist.main.18.643btzX2tzX2uF&algo_pvid=9c0ffc77-d1bb-41ed-be80-74b6d191e596&algo_exp_id=9c0ffc77-d1bb-41ed-be80-74b6d191e596-17&pdp_ext_f=%7B"order"%3A"645"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21GBP%212.03%211.20%21%21%2118.50%2110.91%21%4021038e1e17710245811445933e68f3%2112000044281468940%21sea%21UK%216184487227%21X%211%210%21n_tag%3A-29919%3Bd%3Ac180728d%3Bm03_new_user%3A-29895&curPageLogUid=u78q5w6n49sm&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008221413637%7C_p_origin_prod%3A) |
| 5V 8A Boost Converter | 1 | £0 | Powers LEDs + logic | [link](https://www.aliexpress.com/item/1005006985286655.html?spm=a2g0o.detail.0.0.f228Aa8AAa8A48&mp=1&pdp_npi=6%40dis%21GBP%21GBP%202.94%21GBP%202.72%21%21GBP%202.72%21%21%21%40211b80c217710246430623058efbd4%2112000038947905287%21ct%21UK%216184487227%21%211%210%21) |
| Momentary Button | 1 | £0 | Blade control | [link](https://www.aliexpress.com/item/1005006477375437.html?spm=a2g0o.detail.0.0.78eeFHyIFHyI6b&mp=1&pdp_npi=6%40dis%21GBP%21GBP%201.55%21GBP%201.54%21%21GBP%201.54%21%21%21%40211b80c217710246653933487efbd4%2112000037343711749%21ct%21UK%216184487227%21%211%210%21) |
| Kill Switch | 1 | £0 | Battery cutoff | [link](https://www.aliexpress.com/item/1005008871215158.html?spm=a2g0o.detail.0.0.28b0SPz9SPz9iQ&mp=1&pdp_npi=6%40dis%21GBP%21GBP%201.59%21GBP%201.59%21%21GBP%201.59%21%21%21%40211b80c217710246895443880efbd4%2112000047030832076%21ct%21UK%216184487227%21%211%210%21) |
| Donor Lightsaber Hilt | 1 | £0 | Housing and handle | [link](https://www.aliexpress.com/item/1005009604577083.html?spm=a2g0o.cart.0.0.77b638daHqArn0&mp=1&pdp_npi=6%40dis%21GBP%21GBP%2044.03%21GBP%2017.79%21%21GBP%2017.79%21%21%21%40211b80c217710247287974590efbd4%2112000049605763588%21ct%21UK%216184487227%21%211%210%21) |
| Heatshrink Tubing | — | £0 | Insulating solder joints | [link](https://www.aliexpress.com/item/1005010748539897.html?spm=a2g0o.detail.0.0.6b6eonC8onC88c&mp=1&pdp_npi=6%40dis%21GBP%21GBP%203.04%21GBP%201.49%21%21GBP%201.49%21%21%21%40211b80c217710247448534865efbd4%2112000053384925088%21ct%21UK%216184487227%21%211%210%21) |
| Wires (Silicone 20–22 AWG) | — | £0 | General wiring | [link](https://www.aliexpress.com/item/1005007501110173.html?spm=a2g0o.cart.0.0.77b638daHqArn0&mp=1&pdp_npi=6%40dis%21GBP%21GBP%201.75%21GBP%201.70%21%21GBP%201.70%21%21%21%40211b80c217710247271364558efbd4%2112000050331885021%21ct%21UK%216184487227%21%211%210%21) |
| 18650 Battery Holder | 1 | £0 | Holds battery securely | [link](https://www.aliexpress.com/item/1005009467208586.html?spm=a2g0o.cart.0.0.3df838daCfJPNY&mp=1&pdp_npi=6%40dis%21GBP%21GBP%201.99%21GBP%201.99%21%21GBP%201.99%21%21%21%40211b80c217710249293498699efbd4%2112000049192729834%21ct%21UK%216184487227%21%211%210%21) |
| Packing Foam | — | £4-5 | Blade diffusion + LED protection | [link](https://www.aliexpress.com/item/1005005232963238.html?spm=a2g0o.productlist.main.1.6f983cc7iZVjzg&algo_pvid=0a834e7e-b6bf-4050-b2ce-d7e95d4bdce3&algo_exp_id=0a834e7e-b6bf-4050-b2ce-d7e95d4bdce3-0&pdp_ext_f=%7B"order"%3A"40"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21GBP%2111.07%214.43%21%21%2114.63%215.85%21%402103864c17711140218955538e7f5b%2112000032299199087%21sea%21UK%216184487227%21X%211%210%21n_tag%3A-29919%3Bd%3Ac180728d%3Bm03_new_user%3A-29895&curPageLogUid=wlv6exMdyqhc&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005232963238%7C_p_origin_prod%3A) |
| Total cost | — | £4-5 | - | - |


## Project Summary

This build uses:
- 4× WS2812B LED strips for a bright NeoPixel blade  
- Arduino Nano for animations and button control  
- DFPlayer Mini for ignition, hum, and shutdown sounds  
- 18650 battery with USB‑C charging  
- 5V boost converter to power everything  
- Kill switch to prevent battery drain  

The goal is a smooth, bright, sound-enabled saber on a budget.

## Wiring Overview


Current wiring plan:

- Battery → Kill Switch → Boost Converter → 5V  
- TP4056 connects directly to battery for charging  
- Arduino, DFPlayer, LEDs all run from 5V boost  
- All grounds connected together  
- One data line from Arduino to 2 LED strips out of 4  

![Circuit Diagram](https://codeberg.org/charginmonkey/NeopixelSaber/raw/branch/main/images/circuit_image.png)

## Code

The code will be stored in:

`/code/main.ino`

This contains the complete lightsaber logic, animations, sound engine, and button handling.

## Models


![chassis model](https://codeberg.org/charginmonkey/NeopixelSaber/raw/branch/main/images/Screenshot%202026-02-15%20005607.png)
![chasis in hilt model](https://codeberg.org/charginmonkey/NeopixelSaber/raw/branch/main/images/Screenshot%202026-02-15%20005648.png)
![Labelled model](https://codeberg.org/charginmonkey/NeopixelSaber/raw/branch/main/images/Screenshot%202026-02-15%20010150.png)
https://www.tinkercad.com/things/59F4xZ3Vbe6-neosaber

## How to Use This Project

Using the saber is straightforward:

- Press the main button once to ignite the blade with a full LED extension and ignition sound.
- Tap the button while the blade is on to trigger clash effects.
- Hold the button to power the blade off with a retraction animation and shutdown sound.
- Use the kill switch when storing the saber to fully disconnect the battery and prevent idle drain.
- Charge the saber through the USB‑C port on the TP4056 module. The onboard LEDs indicate charging status.
- While active, the saber plays a looping hum and synchronizes all sound effects with the LED animations.

## Sound Effect Naming Scheme (Used by This Project)

Place all sound files inside the `/mp3` folder on the DFPlayer Mini SD card.
Name them exactly like this:

- `0001.mp3` — Ignition
- `0002.mp3` — Retraction
- `0003.mp3` — Hum loop
- `0004.mp3` — Imperial March
- `0005.mp3` — Force Theme 1
- `0006.mp3` — Force Theme 2

All files must be:
- MP3 format
- 44.1 kHz
- 16‑bit
- Mono
- Named with **four digits** (e.g., `0001.mp3`)

