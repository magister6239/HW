USE STUD new

INDEX ON fio TAG FIO

SET ORDER TO FIO
GO TOP

SEEK "Timur"
if FOUND()
    ? fio, dr, gender, stip
ENDIF
