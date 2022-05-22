
# Simple Stepper

*A library for the **Arduino**.*

<br>

A bare minimum but really fast and simple stepper library. It relies on Timer1 interrupts and direct port manipulations via Pin library to produce extremely smooth stepping signal. It doesn't block as long as you have processing power left. It supports changing the tick rate of the stepper signals to drive the motor faster or slower. It doesn't support acceleration or deceleration control. The usage is very straight forward, basically you just need to provide the STEP and DIR pin numbers, steps, direction and tick rate. The rest of the "API" is pretty much self-explanatory. Base on the author tests on an Arduino Nano 3.0, it is able to drive a 1.8 degree Nema 17 motor with 1/128 microsteps with reasonable speed with still have processing power left for the rest of your code. 

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

[Badge Windows]: https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=Windows&logoColor=white
[Badge Linux]: https://img.shields.io/badge/Linux-10B981?style=for-the-badge&logo=Linux&logoColor=white
[Badge MacOS]: https://img.shields.io/badge/MacOS-lightgray?style=for-the-badge&logo=MacOS&logoColor=white
