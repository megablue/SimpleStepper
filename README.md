
# Simple Stepper    [![Badge License]][License]

*A **Minimal** / **Fast** / **Simple** **Arduino** library.*

<br>


Relies on `Timer1 Interrupts` and `Direct Port Manipulations` via <br>
the Pin library to produce extremely smooth stepping signal.







<br>

## Features

- Doesn't block as long as you have processing power left.
- Modifyable tick rate for slower / faster motor speed.

<br>
<br>

## Unsupported

- Acceleration / Deceleration

<br>
<br>

## Usage

Simply provide the `STEP` & `DIR` pin numbers, steps, direction <br>
and tick rate, the rest is pretty much self-explanatory.

<br>
<br>

## Tested

With an **Arduino Nano 3.0**, it is able to drive a `1.8° Nema 17` <br> 
motor with `1/128` microsteps with reasonable speed with still <br>
have processing power left for the rest of your code. 


<br>
<br>

## Installation

<br>

1. **[Download]** or **Clone** this repository.

    Clone with:
  
    ```sh
    git clone https://github.com/megablue/SimpleStepper
    ```
    
    <br>
  
2. Move the ***cloned*** / ***extracted*** folder to:

    ```
    Arduino/lib/targets/libraries
    ```

    ### Arduino Folder

    *You can find the folder under:*

    ![Badge Windows] <br>
    `C:\Users\<User>\Documents\Arduino`

    ![Badge MacOS] <br>
    `/Users/<User>/Documents/Arduino`

    ![Badge Linux] <br>
    `/home/<User>/Arduino`

<br>


<!----------------------------------------------------------------------------->

[Download]: https://github.com/megablue/SimpleStepper/archive/refs/heads/master.zip
[License]: LICENSE

[Badge License]: https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge
[Badge Windows]: https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=Windows&logoColor=white
[Badge Linux]: https://img.shields.io/badge/Linux-10B981?style=for-the-badge&logo=Linux&logoColor=white
[Badge MacOS]: https://img.shields.io/badge/MacOS-lightgray?style=for-the-badge&logo=MacOS&logoColor=white
