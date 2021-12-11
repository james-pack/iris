Intermediate Astrometry Data (IAD)
Residual records for the Hipparcos Re-reduction (van Leeuwen, 2007)
Source: Hipparcos-2 Interactive Data Access Tool (2014)

Acknowledgements: Floor van Leeuwen <fvl@ast.cam.ac.uk>
                  Daniel Michalik <daniel@skyentist.de>
3 September 2021

This ASCII dataset was exported from the Hipparcos-2 Interactive Data Access
Tool (IDAT; https://www.cosmos.esa.int/web/hipparcos/interactive-data-access;
"the Java tool"). The astrometric solution provided in the tool is
self-consistent, but not numerically identical to the data provided on the DVD
that accompanied the Hipparcos Re-reduction book by van Leeuwen (2007;
hereforth Hip2-DVD).

The format of the exported files mimics the format of the residual records that
were provided on the Hip2-DVD (see book, Table G.8). However, additional header
lines are available containing more auxiliary information as well as the
reference astrometric parameters. Furthermore, the residual records now
indicate which transits were rejected in the final astrometric solution 
(SRES <= 0).


Byte-by-byte description of the data
--------------------------------------------------------------------------------
Line 7 (first header line, excluding comments/labels in the count)

The same fields and format as the header in Hip2-DVD Table G.8. Two columns
have been renamed to better match the data they contain: NRES instead of NOB,
F1 instead of NR. Data taken from the (binary) epoch astrometry files
provided with the Java tool.
--------------------------------------------------------------------------------
   Bytes Format Units   Label    Explanations
--------------------------------------------------------------------------------
  3 -  8  I6                 HIP      Hipparcos identifier
 10 - 15  I6                 MCE      Main-catalogue entry (1)
 17 - 19  I3                 NRES     Number of residual records (2)
 22 - 22  I1                 NC       Number of components
 25 - 27  I3                 isol_n   Solution type (3)
 32 - 35  I4                 SCE      Supplement-catalogue entry
 37 - 42  F6.2               F2       Goodness of fit
 44 - 45  I2                 F1       Percentage rejected (4)
--------------------------------------------------------------------------------
Note (1): The MCE field in the Hip2-DVD data internally used an unsigned short
integer, which led to an overrun from index 32767 to -32768 when read with a
signed short. This was corrected here.

Note (2): NRES corresponds to the number of residual records available for this
source. The residual record file of a given source is therefore always 
(13 + NRES) lines long: 13 header lines including comments/labels, plus the
actual residual records.

Note (3): See van Leeuwen (2007), Section 3.5, for a discussion of the
different solution types.

Note (4): F1 was stored as an integer in the epoch astrometry headers. That
means the number given is the actual percentage rounded down to the nearest
integer. 
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
Line 9 (second header line, excluding comments/labels in the count)

Contains auxiliary information. Data taken from the main astrometric
catalogue files provided with the Java tool (binary files). 
--------------------------------------------------------------------------------
  3 - 9   F7.4   mag         Hp       Hp magnitude, see ESA (1997), Field H44
 11 - 16  F6.3   mag         B-V      B-V colour index, see ESA (1997), Field H37
 18 - 18  I1                 VarAnn   Reference to variability annex, see ESA (1997), Field H53
 25 - 27  I3                 NOB      Number of observations (1)
 29 - 31  I3                 NR       Number of rejected observations (2)
--------------------------------------------------------------------------------
Note (1): The number of observations processed in the astrometric solution of
this source, including the NR rejected observations. For most sources NOB is
identical to the number of residuals available (first header line, field NRES).
For 6617 sources the two numbers differ. This indicates some data corruption in
the residual records of these sources. See Brandt et al. (2021), Section 4,
for a detailed discussion. These authors also offer an ad-hoc correction to the
residual records for the 6617 sources affected.
	
Note (2): The number of observations rejected in the astrometric solution of
this source. These are marked with negative/zero sigma abscissa residuals
(SRES) in the residual records. Note that there are currently 89 sources where
NR does not equal the number of records with negative/zero sigmas. Since the
origin of this issue is not understood, these should be treated with extra care.
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
Line 11 (third header line, excluding comments/labels in the count) 

Contains the reference astrometric parameters, against which the residuals are
expressed, and their corresponding uncertainties. Data taken from the main
astrometric catalogue files provided with the Java tool (binary files). 

All sources list the five main astrometric parameters (and their uncertainties)
first. Sources with 7/9 parameter or VIM solutions additionally list the higher
order terms of their astrometric solution (and the corresponding
uncertainties). Sources with stochastic solutions additionally list the
cosmic dispersion parameter. The solution type is given in the first header
line, field isol_n modulo 10, i.e. by the least significant digit of isol_n.
Additional fields that are not applicable are marked with "---".

Note: For sources with a 7 parameter, 9 parameter, or VIM solution, the
residuals are relative to the full 7 parameter, 9 parameter, or VIM solutions.
This is in contrast to the original Hipparcos reduction (ESA, 1997), where the
residuals are always defined with respect to the skypath described by only the
first five parameters, regardless of solution type.
--------------------------------------------------------------------------------
  3 - 14  F12.8 deg         RAdeg    Right Ascension
 16 - 27  F12.8 deg         DEdeg    Declination
 29 - 36  F8.2  mas         Plx      Parallax
 38 - 45  F8.2  mas/yr      pmRA     Proper motion in Right Ascension 
 47 - 54  F8.2  mas/yr      pmDE     Proper motion in Declination
 56 - 61  F6.2  mas         e_RA     Formal error on RAdeg
 63 - 68  F6.2  mas         e_DE     Formal error on DEdeg
 70 - 75  F6.2  mas         e_Plx    Formal error on Plx
 77 - 82  F6.2  mas/yr      e_pmRA   Formal error on pmRA
 84 - 89  F6.2  mas/yr      e_pmDE   Formal error on pmDE
 91 - 96  F6.2  mas/yr2     dpmRA    Acceleration in Right Ascension (7p, 9p)
 98 - 103 F6.2  mas/yr2     dpmDE    Acceleration in Declination (7p, 9p)
105 - 110 F6.2  mas/yr2     e_dpmRA  Formal error on dpmRA (7p, 9p)
114 - 119 F6.2  mas/yr2     e_dpmDE  Formal error on dpmDE (7p, 9p)
123 - 128 F6.2  mas/yr3     ddpmRA   Acceleration change in Right Ascension (9p)
131 - 136 F6.2  mas/yr3     ddpmDE   Acceleration change in Declination (9p)
139 - 144 F6.2  mas/yr3     e_ddpmRA Formal error on ddpmRA (9p)
149 - 154 F6.2  mas/yr3     e_ddpmDE Formal error on ddpmDE (9p)
159 - 164 F6.2  mas         upsRA    VIM in Right Ascension (VIM)
167 - 172 F6.2  mas         upsDE    VIM in Declination (VIM)
175 - 180 F6.2  mas         e_upsRA  Formal error on upsRA (VIM)
184 - 189 F6.2  mas         e_upsDE  Formal error on upsDE (VIM)
193 - 198 F6.2  mas         var      Cosmic dispersion added (stochastic)
--------------------------------------------------------------------------------
Note (7p, 9p): Applicable to 7p and 9p solutions only; isol_n ending in 7 or 9.
"---" for all other solution types.

Note (9p): Applicable to 9p solutions only; isol_n ending in 9. "---" for all
other solution types.

Note (VIM): Applicable to VIM solutions only; isol_n ending in 3. "---" for all
other solution types.

Note (stochastic): Applicable to stochastic solutions only; isol_n ending in 1.
"---" for all other solution types.
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
Line 14 and all subsequent lines

Residual records: "NRES" data records per source.

The same fields (in the same order) as the data records in Hip2-DVD Table G.8.
Minor format changes in the field width and the number of significant
digits of EPOCH and PARF. Data taken from the (binary) epoch astrometry files
provided with the Java tool.
--------------------------------------------------------------------------------
  3 - 6   I4                 IORB     Orbit Number
  8 - 14  F7.4   yr-1991.25  EPOCH    Epoch
 16 - 22  F7.4               PARF     Parallax factor
 24 - 30  F7.4               CPSI     cos(psi) (1)
 32 - 38  F7.4               SPSI     sin(psi) (1)
 40 - 46  F7.2   mas         RES      Abscissa residual 
 48 - 53  F6.2   mas         SRES     Formal error on abscissa residual (2)
--------------------------------------------------------------------------------
Note (1): The Hipparcos-2 angle psi is related to the Gaia scan angle theta as 
theta = pi/2 - psi. See Brandt et al. (2021), Section 2.
Note (2): Rejected observations are marked as negative or zero (0.00) values.
--------------------------------------------------------------------------------


References:
- ESA, 1997, The Hipparcos and Tycho Catalogues, ESA SP-1200
- van Leeuwen, F. 2007, Hipparcos, the New Reduction of the Raw Data:
Astrophysics and Space Science Library, Volume 350. ISBN 978-1-4020-6341-1.
Springer Science+Business Media B.V., 2007. doi:10.1007/978-1-4020-6342-8
- G. M. Brandt, D. Michalik, T. Brandt, Y. Li, T. Dupuy, Y. Zeng 2021, HTOF: A
new open-source tool for analyzing Hipparcos, Gaia, and future astrometric
missions, AJ, in press
