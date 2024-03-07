-- IEEE library
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
  
ENTITY multiplier_test IS
END multiplier_test;
 
ARCHITECTURE behavior OF multiplier_test IS 
 
 -- definition of inputs and outputs
  -- inputs:  a1, a0, b1, b0
  -- outputs: out3, out2, out1, out0
  
-- ATTENTION!
   -- The component name (COMPONENT <name>) must be equal to the tested component name
   -- In this case: COMPONENT seq_detector
   -- The input and output names (COMPONENT seq_detector) must be equal to the names in the tested design
 
   COMPONENT algebra_4x2
   PORT(
      a1, a0, b1, b0 : IN  std_logic;
      out3, out2, out1, out0 : OUT  std_logic
   );
   END COMPONENT;
    
   SIGNAL a1 : std_logic := '0';
   SIGNAL a0 : std_logic := '0';
   SIGNAL b1 : std_logic := '0';
   SIGNAL b0 : std_logic := '0';

   SIGNAL out3, out2, out1, out0 : std_logic;
 
BEGIN
 
   uut: algebra_4x2 PORT MAP (
     a1 => a1,
     a0 => a0,
     b1 => b1,
     b0 => b0,
     out3 => out3,
     out2 => out2,
     out1 => out1,
     out0 => out0
   );
 
   stim_proc: PROCESS
   BEGIN		


      FOR i IN 0 TO 1 LOOP
         FOR j IN 0 TO 1 LOOP
            FOR k IN 0 TO 1 LOOP 
               FOR l IN 0 TO 1 LOOP
                  wait FOR 20 ns;
                  b0 <= NOT(b0);  		
               END LOOP;
               b1 <= NOT(b1);
            END LOOP;
            a0 <= NOT(a0);
         END LOOP;
         a1 <= NOT(a1);
      END LOOP;
      
      ASSERT FALSE
        REPORT " Simulation finished. Check the waveforms. "
          SEVERITY failure;									
		
   END PROCESS;

END;
