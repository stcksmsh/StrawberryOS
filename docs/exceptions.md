# Exceptions
### ESR_EL1 register
The ESR_EL1 register is 64 bit and has the following structure
| 63:56 | 55:32 | 31:26 | 25 | 24:0 |
| ----- | ----- | ----- | -- | ---- |
| RES0 | ISS2 | EC | IL | ISS |

Where the different fields are:
> - RES0 - reserved
> - ISS2 - ISS2 encoding for an exception from a *Data Abort* (EC == $0b100100$ or $100101$)
> - EC - exception class, gives the cause of the exception and ISS encoding, see [EC table](#ec-table)



##### EC table
**See page D19-6439 of the manual for more information, I'm only writing what I use**
| EC | Explanation |
| -- | ----------- |
| $0b000000$ | Unknown reason |
| $0b010001$ | SVC instruction execution in **AArch32** state | 
| $0b010101$ | SVC instruction execution in **AArch64** state | 
