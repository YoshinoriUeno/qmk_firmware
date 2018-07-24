#ifndef SPLIT_COMM_H
#define SPLIT_COMM_H

// Buffers for master - slave communication
#define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
#define SERIAL_MASTER_BUFFER_LENGTH MATRIX_ROWS/2

extern volatile uint8_t serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH];
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];
#ifdef SERIAL_USE_MULTI_TRANSACTION
extern uint8_t slave_buffer_change_count;
#endif

void serial_master_init(void);
void serial_slave_init(void);
int serial_update_buffers(int master_changed);

#endif /* SPLIT_COMM_H */