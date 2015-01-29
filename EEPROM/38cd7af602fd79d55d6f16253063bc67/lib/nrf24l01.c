
#include "hw_config.h"
#include "spi.h"
#include "nrf24l01.h"

const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; // send address
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; // send address

void bsp_nrf24l01_gpio_init (void)
{
	sbi(NRF24L01_CS_DIR, NRF24L01_CS_PIN_NO);
	sbi(NRF24L01_CE_DIR, NRF24L01_CE_PIN_NO);
	cbi(NRF24L01_IRQ_DIR, NRF24L01_IRQ_PIN_NO);

	bsp_spi_gpio_init();
}


// Initialize the IO port 24L01
void bsp_nrf24l01_init (void)
{
	bsp_spi_init();

	bsp_set_spi_speed(SPI_SPEED_LOW);

	// start transmission
	bsp_readwritebyte_spi(0xff);	

	LOW_24L01_CE;
	HIGH_24L01_CSN;
	
}

// Check whether there 24L01
// Return value: 0 success; 1, failure
u8 nRF24L01_Check (void)
{

	u8 buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
	u8 i;
	
	bsp_set_spi_speed (SPI_SPEED_HIGH); // spi speed 9Mhz (24L01 maximum SPI clock is 10Mhz)
	
	nRF24L01_Write_Buf (NRF24L01_WRITE_REG + TX_ADDR, buf, 5); // write 5 bytes of the address.
	nRF24L01_Read_Buf (TX_ADDR, buf, 5); // read the address written
	
	for (i = 0; i<5; i++) 
		if (buf[i] != 0XA5) 
			break;
		
	if (i != 5) 
		return 1; // error detection 24L01
		
	return 0; // detect 24L01


}

// SPI write register
// Reg: register address specified
// Value: The value to write
u8 nRF24L01_Write_Reg (u8 reg, u8 value)
{
	u8 status;
	
	LOW_24L01_CSN; // Enable SPI transfer
	
	status = bsp_readwritebyte_spi (reg); // send the register number
	bsp_readwritebyte_spi (value); // write registers
	
	HIGH_24L01_CSN; // SPI transfer ban
	
	return (status); // return status values
}

// Read SPI register values
// Reg: register to read
u8 nRF24L01_Read_Reg (u8 reg)
{
	u8 reg_val;

	LOW_24L01_CSN; // Enable SPI transfer

	bsp_readwritebyte_spi (reg); // send the register number
	reg_val = bsp_readwritebyte_spi (0XFF); // read register

	HIGH_24L01_CSN; // SPI transfer ban

	return (reg_val); // return status values
}

// Read in the specified location data in a specified length
// Reg: register (location)
// * PBuf: data pointer
// Len: data length
// Return value, the value of the read status register

u8 nRF24L01_Read_Buf (u8 reg, u8 * pBuf, u8 len)
{
	u8 status, u8_ctr;

	LOW_24L01_CSN; // Enable SPI transfer

	status = bsp_readwritebyte_spi (reg); // send the register values (location), and read the status value
	for (u8_ctr=0; u8_ctr<len; u8_ctr++) 
		pBuf[u8_ctr] = bsp_readwritebyte_spi(0XFF); // read data

	HIGH_24L01_CSN; // turn off SPI transfer

	return status; // return status value read
}

// Write the specified length at the specified location data
// Reg: register (location)
// * PBuf: data pointer
// Len: data length
// Return value, the value of the read status register
u8 nRF24L01_Write_Buf (u8 reg, u8 * pBuf, u8 len)
{
	u8 status, u8_ctr;
	
	LOW_24L01_CSN; // Enable SPI transfer
	
	status = bsp_readwritebyte_spi (reg); // send the register values (location), and read the status value
	
	for (u8_ctr=0;u8_ctr<len;u8_ctr++) 
		bsp_readwritebyte_spi(*pBuf++); // write data
		
	HIGH_24L01_CSN; // turn off SPI transfer
	
	return status; // return status value read
}

// Start to send a data NRF24L01
// Txbuf: the first address data to be transmitted
// Return value: Send completed state
u8 nRF24L01_TxPacket (u8 * txbuf)
{
	u8 sta;
	
	bsp_set_spi_speed(SPI_SPEED_HIGH); // spi speed 9Mhz (24L01 maximum SPI clock is 10Mhz)
	
	LOW_24L01_CE;
	nRF24L01_Write_Buf (WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH); // write data to the TX BUF 32 bytes
	HIGH_24L01_CE; // start transmission
	
	while (inp(NRF24L01_IRQ_PIN, NRF24L01_IRQ_PIN_NO) != 0); // wait for transmission complete
	sta = nRF24L01_Read_Reg (STATUS); // read status register
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + STATUS, sta); // Clear interrupt flag TX_DS or MAX_RT
	if (sta & MAX_TX) // maximum number of retransmissions
	{
		nRF24L01_Write_Reg (FLUSH_TX, 0xff); // Clear TX FIFO registers
		return MAX_TX;
	}
	if (sta & TX_OK) // send the completed
	{
		return TX_OK;
	}
	
	return 0xff; // send failed for other reasons
	
}

// Start to send a data NRF24L01
// Txbuf: the first address data to be transmitted
// Return value: 0, receive completed; other, error codes
u8 nRF24L01_RxPacket (u8 * rxbuf)
{
	u8 sta;

	bsp_set_spi_speed(SPI_SPEED_HIGH); // spi speed 9Mhz (24L01 maximum SPI clock is 10Mhz)
	
	sta = nRF24L01_Read_Reg (STATUS); // read status register
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + STATUS, sta); // Clear interrupt flag TX_DS or MAX_RT
	
	if (sta & RX_OK) // receive data
	{
		nRF24L01_Read_Buf (RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH); // read data
		nRF24L01_Write_Reg (FLUSH_RX, 0xff); // clear the RX FIFO registers
		return 0;
	}
	
	return 1; // did not receive any data
}

// This function initializes NRF24L01 to RX mode
// Set RX address, write RX data width, select the RF channel, baud rate and LNA HCURR
// When CE high, the RX mode is entered, and can receive the data
void nRF24L01_RX_Mode (void)
{
	LOW_24L01_CE;
	
	nRF24L01_Write_Buf (NRF24L01_WRITE_REG + RX_ADDR_P0, (u8 *) RX_ADDRESS, RX_ADR_WIDTH); // write node address RX

	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + EN_AA, 0x01); // enable the automatic response channel 0
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + EN_RXADDR, 0x01); // Enable receiver address channel 0
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + RF_CH, 40); // set the RF communication frequency
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); // select a valid data width of the channel 0
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + RF_SETUP, 0x0f); // set the TX emission parameters, 0db gain, 2Mbps, Low Noise Gain Open
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + CONFIG, 0x0f); // configure the basic parameters of the model work; PWR_UP, EN_CRC, 16BIT_CRC, receive mode
	
	HIGH_24L01_CE; // CE is high, into the receive mode
}

// This function initializes NRF24L01 to TX mode
// Set TX address and write data width of the TX, RX set the address auto-answer, fill TX transmit data, select the RF channel, baud rate and LNA HCURR
// PWR_UP, CRC Enable
// When CE high, the RX mode is entered, and can receive the data
// CE is taller than 10us, then start sending.
void nRF24L01_TX_Mode (void)
{
	LOW_24L01_CE;
	
	nRF24L01_Write_Buf (NRF24L01_WRITE_REG + TX_ADDR, (u8 *) TX_ADDRESS, TX_ADR_WIDTH); // Write TX node address
	nRF24L01_Write_Buf (NRF24L01_WRITE_REG + RX_ADDR_P0, (u8 *) RX_ADDRESS, RX_ADR_WIDTH); // set the TX node address, mainly in order to enable ACK

	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + EN_AA, 0x01); // enable the automatic response channel 0
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + EN_RXADDR, 0x01); // Enable receiver address channel 0
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + SETUP_RETR, 0x1a); // set up automatic retransmission interval: 500us + 86us; largest auto retransmissions: 10
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + RF_CH, 40); // set the RF channel 40
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + RF_SETUP, 0x0f); // set the TX emission parameters, 0db gain, 2Mbps, Low Noise Gain Open
	nRF24L01_Write_Reg (NRF24L01_WRITE_REG + CONFIG, 0x0e); // configure the basic parameters of the model work; PWR_UP, EN_CRC, 16BIT_CRC, receive mode, turn on all interrupts
	
	HIGH_24L01_CE; // CE is high, 10us start sending
}


