C============================= implicitbug.f =============================
C  PURPOSE:
C    Demonstrate implicit typing pitfalls in FORTRAN 77.
C
C  WHAT YOU SHOULD SEE:
C    Program compiles and runs, but prints a wrong average/variance.
C
C  TASK:
C    1) Run and record incorrect output.
C    2) Diagnose using WRITE debugging and compiler warnings.
C    3) Fix by explicitly declaring EVERY variable and correcting typos.
C=======================================================================

      PROGRAM IMPLICITBUG
C     NOTE: Intentionally missing some declarations.
C     In F77, variables starting I-N default INTEGER; others default REAL.

      INTEGER N
      REAL DATA(10)
      REAL AVG, VAR

      DATA DATA / 1.0, 2.0, 3.0, 4.0, 5.0,
     &            6.0, 7.0, 8.0, 9.0, 10.0 /

      N = 10

      CALL STATS_BAD(N, DATA, AVG, VAR)

      WRITE(*,*) 'N   =', N
      WRITE(*,*) 'AVG =', AVG
      WRITE(*,*) 'VAR =', VAR
      WRITE(*,*) 'Expected AVG near 5.5, VAR near 8.25'

      STOP
      END

      SUBROUTINE STATS_BAD(N, X, AVG, VAR)
      INTEGER N
      REAL X(N)
      REAL AVG, VAR

      INTEGER I
      REAL SUM
      REAL SUMSQ

      SUM   = 0.0
      SUMSQ = 0.0

      DO 10 I = 1, N
         SUM  = SUM + X(I)
   10 CONTINUE

      AVG = SUM / N

      DO 20 I = 1, N
         SUMSQ = SUMSQ + (X(I) - AVG) * (X(I) - AVG)
   20 CONTINUE

      VAR = SUMSQ / N

      RETURN
      END
C========================== END OF IMPLICITBUG.F =========================
