-- fsm.vhd: Finite State Machine
-- Author: Petr Knetl (xknetl00)
-- E-mail: xknetl00@stud.fit.vutbr.cz
--
library ieee;
use ieee.std_logic_1164.all;
-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity fsm is
port(
   CLK         : in  std_logic;
   RESET       : in  std_logic;

   -- Input signals
   KEY         : in  std_logic_vector(15 downto 0);
   CNT_OF      : in  std_logic;

   -- Output signals
   FSM_CNT_CE  : out std_logic;
   FSM_MX_MEM  : out std_logic;
   FSM_MX_LCD  : out std_logic;
   FSM_LCD_WR  : out std_logic;
   FSM_LCD_CLR : out std_logic
);
end entity fsm;

-- ----------------------------------------------------------------------------
--                      Architecture declaration
--	(xknetl00 : kod1 = 1255590928 	 kod2 = 12511500208)
-- ----------------------------------------------------------------------------
architecture behavioral of fsm is
   type t_state is (TEST1, TEST2, TEST3, TEST4, TEST5_A, TEST5_B, TEST6_A, TEST6_B, TEST7_A, TEST7_B, TEST8_A,
   TEST8_B, TEST9_A, TEST9_B, TEST10_A, TEST10_B, TEST11, TESTF, PRINT_MESSAGE_CORRECT, PRINT_MESSAGE_INCORRECT, ERROR1, FINISH);
   signal present_state, next_state : t_state;

begin
-- -------------------------------------------------------
sync_logic : process(RESET, CLK)
begin
   if (RESET = '1') then
      present_state <= TEST1;
   elsif (CLK'event AND CLK = '1') then
      present_state <= next_state;
   end if;
end process sync_logic;

-- -------------------------------------------------------
next_state_logic : process(present_state, KEY, CNT_OF)
begin
   case (present_state) is
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST1 => next_state <= TEST1;
      if(KEY(1) = '1') then next_state <= TEST2;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST2 => next_state <= TEST2;
      if(KEY(2) = '1') then next_state <= TEST3;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST3 => next_state <= TEST3;
      if(KEY(5) = '1') then next_state <= TEST4;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST4 => next_state <= TEST4;
      if(KEY(5) = '1') then next_state <= TEST5_A;
      elsif(KEY(1) = '1') then next_state <= TEST5_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST5_A => next_state <= TEST5_A;
      if(KEY(5) = '1') then next_state <= TEST6_A;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST6_A => next_state <= TEST6_A;
      if(KEY(9) = '1') then next_state <= TEST7_A;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST7_A => next_state <= TEST7_A;
      if(KEY(0) = '1') then next_state <= TEST8_A;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST8_A => next_state <= TEST8_A;
      if(KEY(9) = '1') then next_state <= TEST9_A;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST9_A => next_state <= TEST9_A;
      if(KEY(2) = '1') then next_state <= TEST10_A;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST10_A => next_state <= TEST10_A;
      if(KEY(8) = '1') then next_state <= TESTF ;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST5_B => next_state <= TEST5_B;
      if(KEY(1) = '1') then next_state <= TEST6_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST6_B => next_state <= TEST6_B;
      if(KEY(5) = '1') then next_state <= TEST7_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST7_B => next_state <= TEST7_B;
      if(KEY(0) = '1') then next_state <= TEST8_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST8_B => next_state <= TEST8_B;
      if(KEY(0) = '1') then next_state <= TEST9_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST9_B => next_state <= TEST9_B;
      if(KEY(2) = '1') then next_state <= TEST10_B;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST10_B => next_state <= TEST10_B;
      if(KEY(0) = '1') then next_state <= TEST11;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT;
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST11 => next_state <= TEST11;
      if(KEY(8) = '1') then next_state <= TESTF ;
      elsif (KEY(15) = '1') then next_state <= PRINT_MESSAGE_INCORRECT; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TESTF => next_state <= TESTF;
      if(KEY(15) = '1') then next_state <= PRINT_MESSAGE_CORRECT ; 
      elsif (KEY(15 downto 0) /= "0000000000000000") then next_state <= ERROR1;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -

   when PRINT_MESSAGE_INCORRECT => next_state <= PRINT_MESSAGE_INCORRECT;
      if (CNT_OF = '1') then next_state <= FINISH;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when PRINT_MESSAGE_CORRECT => next_state <= PRINT_MESSAGE_CORRECT;
      if (CNT_OF = '1') then next_state <= FINISH;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when FINISH => next_state <= FINISH;
      if (KEY(15) = '1') then next_state <= TEST1; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when others => next_state <= TEST1;
   end case;
end process next_state_logic;

-- -------------------------------------------------------
output_logic : process(present_state, KEY)
begin
   FSM_CNT_CE     <= '0';
   FSM_MX_MEM     <= '0';
   FSM_MX_LCD     <= '0';
   FSM_LCD_WR     <= '0';
   FSM_LCD_CLR    <= '0';

   case (present_state) is
   -- - - - - - - - - - - - - - - - - - - - - - -
   when TEST1 =>
      if (KEY(14 downto 0) /= "000000000000000") then
         FSM_LCD_WR     <= '1';
      end if;
      if (KEY(15) = '1') then
         FSM_LCD_CLR    <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when PRINT_MESSAGE_CORRECT =>
      FSM_CNT_CE     <= '1';
      FSM_MX_LCD     <= '1';
      FSM_LCD_WR     <= '1';
      FSM_MX_MEM     <= '1';
   -- - - - - - - - - - - - - - - - - - - - - - -
   when PRINT_MESSAGE_INCORRECT =>
      FSM_CNT_CE     <= '1';
      FSM_MX_LCD     <= '1';
      FSM_LCD_WR     <= '1';
      FSM_MX_MEM     <= '0';
   -- - - - - - - - - - - - - - - - - - - - - - -
   when FINISH =>
      if (KEY(15) = '1') then
         FSM_LCD_CLR    <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when others =>
      if(KEY(14 downto 0) /= "000000000000000") then FSM_LCD_WR <= '1';
      end if;
      
      if(KEY(15) = '1') then FSM_LCD_CLR <= '1';
      end if;
   end case;
end process output_logic;

end architecture behavioral;

