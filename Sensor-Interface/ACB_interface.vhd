----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07/10/2022 03:50:39 PM
-- Design Name: 
-- Module Name: ACB_interface - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ACB_interface is
    
    Port (In_data: in std_logic_vector(9 downto 0);
        Frame_Valid: in std_logic;
        Line_valid: in std_logic;
        In_clock: in std_logic;
        In_ack: inout std_logic;
        
        out_ack: inout std_logic;
        write_data: out std_logic_vector(63 downto 0)
        );
        
end ACB_interface;

architecture mixed of ACB_interface is

    type FSM is (Idle, onepixel, twopixels, threepixels, fourpixels, fivepixels, sixpixels, one_word);
    signal current_state, next_state : FSM;
    signal written_pixel: std_logic := '0';
    signal write_to : std_logic_vector(5 downto 0);
    
    begin

    clocked_input: process(In_clock)
        begin
        If (line_valid = '1' and frame_valid = '1' and in_ack = '1') then
            If (In_clock'event and In_clock = '1') then
                write_data((to_integer(unsigned(write_to)) + 9) downto to_integer(unsigned(write_to))) <= In_Data; 
                written_pixel <= '1';
            end if;
        end if;
        end process clocked_input;

    FSM_state : process(written_pixel)
        begin
        if(written_pixel = '1') then
            case current_state is
                when Idle=> 
                    If (in_ack = '1') then
                        next_state <= onepixel;
                    else 
                        next_state <= Idle;
                    end if;        
                when Onepixel =>
                    written_pixel <= '0';
                    write_to <= "000000";
                    next_state <= twopixels;   
                when Twopixels =>
                    written_pixel <= '0';
                    write_to <= "001010";
                    next_state <= threepixels; 
                when Threepixels =>
                    written_pixel <= '0';
                    write_to <= "010100";
                    next_state <= fourpixels;        
                when Fourpixels =>
                    written_pixel <= '0';
                    write_to <= "011110";
                    next_state <= Fivepixels;
                when Fivepixels =>
                    written_pixel <= '0';
                    write_to <= "101000";
                    next_state <= Sixpixels;
                when Sixpixels =>
                    written_pixel <= '0';
                    write_to <= "110010"; 
                    next_state <= one_word; 
                when one_word =>
                    written_pixel <='0';
                    in_ack <= '0';
                    write_data(63 downto 60) <= "0000";
                    out_ack <= '1';
                    next_state <= Idle;       
            end case;        
        end if;    
    end process;
    end mixed;
