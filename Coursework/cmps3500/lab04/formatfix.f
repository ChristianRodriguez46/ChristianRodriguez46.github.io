C============================== formatfix.f ==============================
C  PURPOSE:
C    Fixed-format mini-challenges (FORTRAN 77).
C
C  STUDENT INSTRUCTIONS:
C    This file is intentionally broken. Fix ONLY fixed-format issues:
C      - columns (label field, continuation column, statement start column)
C      - comment column (C or * in column 1)
C      - continuation lines (non-blank in column 6)
C      - avoid accidental truncation past column 72
C
C    Do NOT change the intended computations.
C
C  DONE WHEN:
C    Program compiles and prints OK 1 ... OK 13.
C=======================================================================

      PROGRAM FORMATFIX
      CALL TEST01
      CALL TEST02
      CALL TEST03
      CALL TEST04
      CALL TEST05
      CALL TEST06
      CALL TEST07
      CALL TEST08
      CALL TEST09
      CALL TEST10
      CALL TEST11
      CALL TEST12
      CALL TEST13
      STOP
      END

C-----------------------------------------------------------------------
C TEST01 (compile error): statement begins before column 7 (col 6 used).
C Intended: print OK 1
C-----------------------------------------------------------------------
      SUBROUTINE TEST01
C BUG: WRITE begins too early. In fixed form, column 6 is continuation.
      WRITE(*,*) 'OK 1'
      RETURN
      END

C-----------------------------------------------------------------------
C TEST02 (compile error): comment not in column 1.
C Intended: print OK 2
C-----------------------------------------------------------------------
      SUBROUTINE TEST02
C BUG: this line is meant to be a comment, but 'C' is missing in column 1
      WRITE(*,*) 'OK 2'
      RETURN
      END

C-----------------------------------------------------------------------
C TEST03 (compile error): missing continuation marker in column 6.
C Intended: X = 100 + 20 + 3 = 123, then print OK 3 123
C-----------------------------------------------------------------------
      SUBROUTINE TEST03
      INTEGER X
      X = 100 + 20
     &+ 3
      WRITE(*,*) 'OK 3', X
      RETURN
      END

C-----------------------------------------------------------------------
C TEST04 (compile error): label field overflow into column 6.
C Intended: sum 1..5 = 15, then print OK 4 15
C-----------------------------------------------------------------------
      SUBROUTINE TEST04
      INTEGER I, S
      S = 0
      DO 10 I = 1, 5
         S = S + I
   10 CONTINUE
      WRITE(*,*) 'OK 4', S
      RETURN
      END

C-----------------------------------------------------------------------
C TEST05 (wrong output until fixed): label not in columns 1-5.
C Intended: loop executes once, so I = 1 and print OK 5
C-----------------------------------------------------------------------
      SUBROUTINE TEST05
      INTEGER I
      I = 0
   20 I = I + 1
      IF (I .LT. 1) GOTO 20
      IF (I .EQ. 1) THEN
         WRITE(*,*) 'OK 5'
      ELSE
         WRITE(*,*) 'FAIL 5 got', I, 'expected 1'
      ENDIF
      RETURN
      END

C-----------------------------------------------------------------------
C TEST06 (compile error): arithmetic IF statement-start / label placement.
C Intended: X=-1 => OK 6 NEG
C-----------------------------------------------------------------------
      SUBROUTINE TEST06
      INTEGER X
      X = -1
C BUG: make sure this line obeys fixed-format column rules
      IF (X)  100, 200, 300
  100 WRITE(*,*) 'OK 6 NEG'
      RETURN
  200 WRITE(*,*) 'OK 6 ZERO'
      RETURN
  300 WRITE(*,*) 'OK 6 POS'
      RETURN
      END

C-----------------------------------------------------------------------
C TEST07 (compile error): continuation char not in column 6.
C Intended: MSG="FORTRAN 77 fixed-format continuation test"
C-----------------------------------------------------------------------
      SUBROUTINE TEST07
      CHARACTER*60 MSG
      MSG = 'FORTRAN 77 fixed-format ' // 
     & 'continuation test'
      WRITE(*,*) 'OK 7', MSG
      RETURN
      END

C-----------------------------------------------------------------------
C TEST08 (wrong output until fixed): line-too-long / truncation risk.
C Intended: X=10, Y=21, print OK 8 21
C-----------------------------------------------------------------------
      SUBROUTINE TEST08
      INTEGER X, Y
      X = 10
C BUG: This assignment is intentionally too long; fix by shortening or using continuation
      Y = 2 * X + 1 + 0 + 0 + 0 + 0 
     &+ 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0
      IF (Y .EQ. 21) THEN
         WRITE(*,*) 'OK 8', Y
      ELSE
         WRITE(*,*) 'FAIL 8 got', Y, 'expected 21'
      ENDIF
      RETURN
      END

C-----------------------------------------------------------------------
C TEST09 (compile error): statement starts too early (column 6 issue).
C Intended: print OK 9
C-----------------------------------------------------------------------
      SUBROUTINE TEST09
C BUG: statement begins too early
      WRITE(*,*) 'OK 9'
      RETURN
      END

C-----------------------------------------------------------------------
C TEST10 (compile error): continuation line not marked properly.
C Intended: Z=7*6=42, print OK 10 42
C-----------------------------------------------------------------------
      SUBROUTINE TEST10
      INTEGER Z
      Z = 7 *
     & 6
      WRITE(*,*) 'OK 10', Z
      RETURN
      END

C-----------------------------------------------------------------------
C TEST11 (compile error): FORMAT label not in columns 1-5.
C Intended: print OK 11 (using formatted output)
C-----------------------------------------------------------------------
      SUBROUTINE TEST11
      INTEGER K
      K = 11
  901 FORMAT('OK ', I2)
      WRITE(*,901) K
      RETURN
      END

C-----------------------------------------------------------------------
C TEST12 (wrong output until fixed): Hollerith + fixed-format statement start.
C Intended: print OK 12 HELLO
C-----------------------------------------------------------------------
      SUBROUTINE TEST12
C BUG: WRITE begins too early; fix column placement (and keep Hollerith)
      WRITE(*,*) 'OK 12 ', 5HHELLO
      RETURN
      END

C-----------------------------------------------------------------------
C TEST13 (compile error): split character literal without continuation.
C Intended: print full message in one WRITE
C-----------------------------------------------------------------------
      SUBROUTINE TEST13
      CHARACTER*80 MSG
      MSG = 'OK 13: a message that is long enough to need' //
     & ' continuation in fixed form'
      WRITE(*,*) MSG
      RETURN
      END
