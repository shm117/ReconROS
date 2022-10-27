/*
 *                                                        ____  _____
 *                            ________  _________  ____  / __ \/ ___/
 *                           / ___/ _ \/ ___/ __ \/ __ \/ / / /\__ \
 *                          / /  /  __/ /__/ /_/ / / / / /_/ /___/ /
 *                         /_/   \___/\___/\____/_/ /_/\____//____/
 *
 * ======================================================================
 *
 *   title:        Calls library header file
 *
 *   project:      ReconOS
 *   author:       Andreas Agne, University of Paderborn
 *                 Christoph Rüthing, University of Paderborn
 *   description:  ReconOS calls to allow interaction with POSIX-API of
 *                 system calls.
 *
 * ======================================================================
 */

<<reconos_preproc>>

#ifndef RECONOS_CALLS_H
#define RECONOS_CALLS_H

#include "hls_stream.h"
#include "stdint.h"
#include "ap_int.h"

#include "ap_axi_sdata.h"
//#include <sensor_msgs/msg/image.h>

<<generate for HWTOPICSPUB>>
#include <<<include>>>
<<end generate>>

<<generate for HWTOPICSSUB>>
#include <<<include>>>
<<end generate>>

/* == Helper definitions =============================================== */

#define RRBASETYPE 			<<RRBASETYPE>>
#define RRUBASETYPE			<<RRUBASETYPE>>
#define RRBASETYPEBYTES		<<RRBASETYPEBYTES>>

#define OFFSETOF(type, member) ((RRUBASETYPE)(intptr_t)&(((type *)(void*)0)->member) )

/* == Constant definitions ============================================= */

/*
 * General constants
 *
 *   MEMIF_CHUNK_WORDS - size of one memory request in words
 *                       (a request might be split up to meet this)
 */

#if RRBASETYPEBYTES == 4 

	#define MEMIF_CHUNK_WORDS 64
	#define MEMIF_CHUNK_BYTES (MEMIF_CHUNK_WORDS * 4)
	#define MEMIF_CHUNK_MASK  0x000000FF

	#define MEMIF_CMD_READ 0x00000000
	#define MEMIF_CMD_WRITE 0xF0000000

#elif RRBASETYPEBYTES == 8 
	#define MEMIF_CHUNK_WORDS 32
	#define MEMIF_CHUNK_BYTES (MEMIF_CHUNK_WORDS * 8)
	#define MEMIF_CHUNK_MASK  0x00000000000000FF

	#define MEMIF_CMD_READ 0x0000000000000000
	#define MEMIF_CMD_WRITE 0xF000000000000000
#endif
/*
 * Definition of the osif commands
 *
 *   self-describing
 *
 */
#define OSIF_CMD_THREAD_GET_INIT_DATA  			(RRUBASETYPE)0x000000A0
#define OSIF_CMD_THREAD_GET_STATE_ADDR 			(RRUBASETYPE)0x000000A1
#define OSIF_CMD_THREAD_EXIT           			(RRUBASETYPE)0x000000A2
#define OSIF_CMD_THREAD_YIELD          			(RRUBASETYPE)0x000000A3
#define OSIF_CMD_THREAD_CLEAR_SIGNAL   			(RRUBASETYPE)0x000000A4
#define OSIF_CMD_SEM_POST              			(RRUBASETYPE)0x000000B0
#define OSIF_CMD_SEM_WAIT              			(RRUBASETYPE)0x000000B1
#define OSIF_CMD_MUTEX_LOCK            			(RRUBASETYPE)0x000000C0
#define OSIF_CMD_MUTEX_UNLOCK          			(RRUBASETYPE)0x000000C1
#define OSIF_CMD_MUTEX_TRYLOCK         			(RRUBASETYPE)0x000000C2
#define OSIF_CMD_COND_WAIT             			(RRUBASETYPE)0x000000D0
#define OSIF_CMD_COND_SIGNAL           			(RRUBASETYPE)0x000000D1
#define OSIF_CMD_COND_BROADCAST        			(RRUBASETYPE)0x000000D2
#define OSIF_CMD_MBOX_GET              			(RRUBASETYPE)0x000000F0
#define OSIF_CMD_MBOX_PUT              			(RRUBASETYPE)0x000000F1
#define OSIF_CMD_MBOX_TRYGET           			(RRUBASETYPE)0x000000F2
#define OSIF_CMD_MBOX_TRYPUT           			(RRUBASETYPE)0x000000F3
#define OSIF_CMD_MASK                  			(RRUBASETYPE)0x00000FFF
#define OSIF_CMD_YIELD_MASK            			(RRUBASETYPE)0x80000000

#define OSIF_SIGNAL_THREAD_START       			(RRUBASETYPE)0x01000000
#define OSIF_SIGNAL_THREAD_RESUME      			(RRUBASETYPE)0x01000001

#define OSIF_INTERRUPTED               			(RRUBASETYPE)0x000000FF

#define OSIF_CMD_ROS_MESSAGE_SET_SIZE			(RRUBASETYPE)0x000009F0

#define OSIF_CMD_MEMORY_MALLOC					(RRUBASETYPE)0x000000F4
#define OSIF_CMD_MEMORY_FREE					(RRUBASETYPE)0x000000F5
#define OSIF_CMD_MEMORY_GETOBJADDR				(RRUBASETYPE)0x000000F6
#define OSIF_CMD_MEMORY_GETMEMADDR				(RRUBASETYPE)0x000000F7

#define OSIF_CMD_ROS_PUBLISH		   			(RRUBASETYPE)0x00000900
#define OSIF_CMD_ROS_TAKE			   			(RRUBASETYPE)0x00000901
#define OSIF_CMD_ROS_TRYTAKE		   			(RRUBASETYPE)0x00000902

#define OSIF_CMD_ROS_SERVICES_RESPONSE 			(RRUBASETYPE)0x00000910
#define OSIF_CMD_ROS_SERVICES_TRYTAKE  			(RRUBASETYPE)0x00000911	
#define OSIF_CMD_ROS_SERVICES_TAKE 	   			(RRUBASETYPE)0x00000912

#define OSIF_CMD_ROS_ACTIONS_GOAL_TAKE			(RRUBASETYPE)0x00000920
#define OSIF_CMD_ROS_ACTIONS_GOAL_TRYTAKE		(RRUBASETYPE)0x00000921
#define OSIF_CMD_ROS_ACTIONS_GOAL_DECIDE		(RRUBASETYPE)0x00000922
#define OSIF_CMD_ROS_ACTIONS_RESULT_TAKE		(RRUBASETYPE)0x00000923
#define OSIF_CMD_ROS_ACTIONS_RESULT_TRYTAKE		(RRUBASETYPE)0x00000924
#define OSIF_CMD_ROS_ACTIONS_RESULT_SEND		(RRUBASETYPE)0x00000925
#define OSIF_CMD_ROS_ACTIONS_FEEDBACK			(RRUBASETYPE)0x00000926
#define OSIF_CMD_ROS_ACTIONS_CANCEL_TAKE		(RRUBASETYPE)0x00000927
#define OSIF_CMD_ROS_ACTIONS_CANCEL_TRYTAKE		(RRUBASETYPE)0x00000928
#define OSIF_CMD_ROS_ACTIONS_CANCEL_SEND		(RRUBASETYPE)0x00000929

//Clients
#define OSIF_CMD_ROS_SERVICEC_REQUEST 			(RRUBASETYPE)0x00000930
#define OSIF_CMD_ROS_SERVICEC_TRYTAKE  			(RRUBASETYPE)0x00000931	
#define OSIF_CMD_ROS_SERVICEC_TAKE 	   			(RRUBASETYPE)0x00000932

#define OSIF_CMD_ROS_ACTIONC_GOAL_SEND			(RRUBASETYPE)0x00000940
#define OSIF_CMD_ROS_ACTIONC_GOAL_TRYTAKE		(RRUBASETYPE)0x00000941
#define OSIF_CMD_ROS_ACTIONC_GOAL_TAKE			(RRUBASETYPE)0x00000942
#define OSIF_CMD_ROS_ACTIONC_RESULT_SEND		(RRUBASETYPE)0x00000943
#define OSIF_CMD_ROS_ACTIONC_RESULT_TAKE		(RRUBASETYPE)0x00000944
#define OSIF_CMD_ROS_ACTIONC_RESULT_TRYTAKE		(RRUBASETYPE)0x00000945

#define OSIF_CMD_ROS_ACTIONC_FEEDBACK_TAKE		(RRUBASETYPE)0x00000946
#define OSIF_CMD_ROS_ACTIONC_FEEDBACK_TRYTAKE	(RRUBASETYPE)0x00000947

#define OSIF_CMD_ROS_ACTIONC_CANCEL_SEND		(RRUBASETYPE)0x00000948
#define OSIF_CMD_ROS_ACTIONC_CANCEL_TAKE		(RRUBASETYPE)0x00000949
#define OSIF_CMD_ROS_ACTIONC_CANCEL_TRYTAKE		(RRUBASETYPE)0x00000950


/*
 * Definition of memif commands
 *
 *   self-describing
 */



/* == Internal functions =============================================== */

/*
 * Writes blocking to a stream using the non-blocking method. Since the
 * non-blocking write is called in a loop, vivado hls enforces sequential
 * order, which is necessary for osif and memif calls.
 *
 *   stream - reference to stream
 *   data   - data to write
 */
inline void stream_write(hls::stream<RRUBASETYPE> &stream, RRUBASETYPE data) {
#pragma HLS inline
	while (!stream.write_nb(data)){}
}

/*
 * Reads blocking from a stream using the non-blocking method. Since the
 * non-blocking read is called in a loop, vivado hls enforces sequential
 * order, which is necessary for osif and memif calls.
 *
 *   stream - reference to stream
 *
 *   @returns read data
 */
inline RRUBASETYPE stream_read(hls::stream<RRUBASETYPE> &stream, hls::stream<RRUBASETYPE> &outputstream, volatile bool &hwt_signal) {
#pragma HLS inline
	RRUBASETYPE data;
	while (!stream.read_nb(data)){ if(hwt_signal){ stream_write(outputstream, OSIF_CMD_THREAD_EXIT);while(1);}}
	return data;
}

/*
 * Reads blocking from a stream using the non-blocking method. Since the
 * non-blocking read is called in a loop, vivado hls enforces sequential
 * order, which is necessary for osif and memif calls.
 *
 *   stream - reference to stream
 *
 *   @returns read data
 */
inline RRUBASETYPE stream_read_memif(hls::stream<RRUBASETYPE> &stream) {
#pragma HLS inline
	RRUBASETYPE data;
	while (!stream.read_nb(data)){}
	return data;
}





/* == Call functions =================================================== */

/*
 * Creates a local ram to be used for mem functions. You may only pass
 * rams created by this macro to mem functions.
 *
 *   type - datatype of the ram 
 *   size - size of the ram
 *   name - name of the ram
 */
#define RAM(type,size,name)\
	type name[size]

/*
 * Initializes the thread and reads from the osif the resume status.
 */
#define THREAD_INIT()\
 	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal);

/*
 * Posts the semaphore specified by handle.
 *
 *   @see sem_post
 */
#define SEM_POST(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_SEM_POST),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Waits for the semaphore specified by handle.
 *
 *   @see sem_wait
 */
#define SEM_WAIT(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_SEM_WAIT),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Locks the mutex specified by handle.
 *
 *   @see pthread_mutex_lock
 */
#define MUTEX_LOCK(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MUTEX_LOCK),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Unlocks the mutex specified by handle.
 *
 *   @see pthread_mutex_unlock
 */
#define MUTEX_UNLOCK(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MUTEX_UNLOCK),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Tries to lock the mutex specified by handle and returns if successful or not.
 *
 *   @see pthread_mutex_trylock
 */
#define MUTEX_TRYLOCK(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MUTEX_TRYLOCK),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Waits for the condition variable specified by handle.
 *
 *   @see pthread_cond_wait
 */
#define COND_WAIT(p_handle,p_handle2)(\
	stream_write(osif_hw2sw, OSIF_CMD_COND_WAIT),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Signals a single thread waiting on the condition variable specified by handle.
 *
 *   @see pthread_cond_signal
 */
#define COND_SIGNAL(p_handle,p_handle2)(\
	stream_write(osif_hw2sw, OSIF_CMD_COND_SIGNAL),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Signals all threads waiting on the condition variable specified by handle.
 *
 *   @see pthread_cond_broadcast
 */
#define COND_BROADCAST(p_handle,p_handle2)(\
	stream_write(osif_hw2sw, OSIF_CMD_COND_BROADCAST),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Puts a single word into the mbox specified by handle.
 *
 *   @see mbox_get
 */
#define MBOX_GET(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MBOX_GET),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Reads a single word from the mbox specified by handle.
 *
 *   @see mbox_put
 */
#define MBOX_PUT(p_handle,data)(\
	stream_write(osif_hw2sw, OSIF_CMD_MBOX_PUT),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, data),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Tries to put a single word into the mbox specified by handle but does not
 * blocks until the mbox gets populated.
 *
 *   @see mbox_tryget
 */
#define MBOX_TRYGET(p_handle,data)(\
	stream_write(osif_hw2sw, OSIF_CMD_MBOX_TRYGET),\
	stream_write(osif_hw2sw, p_handle),\
	data = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal)

/*
 * Tries to read a single word from the mbox specified by handle but does not
 * blocks until the mbox gets free.
 *
 *   @see mbox_tryput
 */
#define MBOX_TRYPUT(p_handle,data)(\
	stream_write(osif_hw2sw, OSIF_CMD_MBOX_TRYPUT),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, data),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 *	Memory functions
 */

#define MEMORY_GETOBJECTADDR(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MEMORY_GETOBJADDR),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define MEMORY_GETMEMORYADDR(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_MEMORY_GETMEMADDR),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define MEMORY_MALLOC(ptr_dest,length)(\
	stream_write(osif_hw2sw, OSIF_CMD_MEMORY_MALLOC),\
	stream_write(osif_hw2sw, ptr_dest),\
	stream_write(osif_hw2sw, length),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define MEMORY_FREE(ptr)(\
	stream_write(osif_hw2sw, OSIF_CMD_MEMORY_FREE),\
	stream_write(osif_hw2sw, ptr))

/************************************************************************************
 * 
 * ROS Extensions 
 * 
 * *********************************************************************************/


#define ROS_MESSAGE_ARRAY_SET_SIZE(p_handle, offset, element_size, size)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_MESSAGE_SET_SIZE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, offset),\
	stream_write(osif_hw2sw, element_size),\
	stream_write(osif_hw2sw, size),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))


//ROS Communication function


#define ROS_PUBLISH(p_handle,p_handle_msg)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_PUBLISH),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SUBSCRIBE_TRYTAKE(p_handle,p_handle_msg, msg_ptr)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	msg_ptr = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SUBSCRIBE_TAKE(p_handle, p_handle_msg )(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw, osif_hw2sw, hwt_signal))


// Extensions for hardware topics
typedef ap_axis<64,1,1,1> t_stream;

<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v4_<<Name>>( <<Name>>, msg){\
	uint64_t ___deserialization_buffer[<<num_msg_elems>>]; \
	uint32_t ___i = 0; \
	ap_axis<64,1,1,1> __tmp_frame; \
	for (uint32_t j = 0; j < <<num_msg_elems>>; j++){ \
		_Pragma ("HLS pipeline")  \
		(<<Name>>).read(__tmp_frame); \
		___deserialization_buffer[j] = __tmp_frame.data; \
	}\
	<<=generate for Primitives=>>
	(msg).<<name>> = ___deserialization_buffer[___i]; \
	___i += 1;  <<=end generate=>>  <<=generate for Arrays=>> for(uint32_t k = 0; k < <<num_elems>>; k++){ \
			(msg).<<name>>.data[k] = ___deserialization_buffer[___i]; \
			___i += 1; \
		}\<<=end generate=>>}
<<end generate>>

<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v4_timing_<<Name>>( <<Name>>, msg){\
	uint64_t ___deserialization_buffer[<<num_msg_elems>>]; \
	uint32_t ___i = 0; \
	ap_axis<64,1,1,1> __tmp_frame; \
	(<<Name>>).read(__tmp_frame); \
	(<<Name>>).read(__tmp_frame); \
	for (uint32_t j = 0; j < <<num_msg_elems>>; j++){ \
		_Pragma ("HLS pipeline")  \
		(<<Name>>).read(__tmp_frame); \
		___deserialization_buffer[j] = __tmp_frame.data; \
	}\
	<<=generate for Primitives=>>
	(msg).<<name>> = ___deserialization_buffer[___i]; \
	___i += 1;  <<=end generate=>>  <<=generate for Arrays=>> for(uint32_t k = 0; k < <<num_elems>>; k++){ \
			(msg).<<name>>.data[k] = ___deserialization_buffer[___i]; \
			___i += 1; \
		}\<<=end generate=>>(<<Name>>).read(__tmp_frame);  \
		}
<<end generate>>

<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v4_timing_<<Name>>( <<Name>>, msg){\
	uint64_t __serialization_buffer[<<num_msg_elems>>]; \
	uint32_t __i = 0; \
	uint32_t __j = 0; \
	write_section : { \
	_Pragma ("HLS protocol") \
	ap_axis<64,1,1,1> __tmp_frame; \
	__tmp_frame.user = 0; \
	__tmp_frame.last = 0; \
	(<<Name>>).write(__tmp_frame); \
	__tmp_frame.user = 1; \
	(<<Name>>).write(__tmp_frame); \
	<<=generate for Primitives=>>
	__serialization_buffer[__i] = (msg).<<name>>; \
	__i += 1;  <<=end generate=>> df_section : {\
	_Pragma ("HLS dataflow") \
	<<=generate for Arrays=>> for(uint32_t k = 0; k < <<num_elems>>; k++){ \
			__serialization_buffer[k] = k ;\
		} \ <<=end generate=>>  for (uint32_t j = 0; j < <<num_msg_elems>>; j++){ \
		__tmp_frame.data = __serialization_buffer[j]; \
	} }\
	__tmp_frame.user = 0; \
	__tmp_frame.last = 1; \
	(<<Name>>).write(__tmp_frame); \
} \
}
<<end generate>>

<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v4_<<Name>>( <<Name>>, msg){\
	uint64_t __serialization_buffer[<<num_msg_elems>>]; \
	uint32_t __i = 0; \
	uint32_t __j = 0; \
	ap_axis<64,1,1,1> __tmp_frame; \
	<<=generate for Primitives=>>
	__serialization_buffer[__i] = (msg).<<name>>; \
	__i += 1;  <<=end generate=>> <<=generate for Arrays=>> for(uint32_t k = 0; k < <<num_elems>>; k++){ \
			__serialization_buffer[__i] = (msg).<<name>>.data[k]; \
			__i += 1; \
		} \ <<=end generate=>>  for (uint32_t j = 0; j < <<num_msg_elems>>; j++){ \
		__tmp_frame.data = __serialization_buffer[__j]; \
		_Pragma ("HLS pipeline")  \
		(<<Name>>).write(__tmp_frame); \
		__j += 1; \
	} \
}
<<end generate>>



<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v5_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	read_section : { \
	<<=generate for Primitives=>>
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>> = __tmp_frame.data;  <<=end generate=>> <<=generate for Arrays=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i++) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i] = __tmp_frame.data; \
		} \ <<=end generate=>>	} \
}
<<end generate>>

<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v5_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	write_section : { \
	<<=generate for Primitives=>>
		__tmp_frame.data = (msg).<<name>>; \
		(<<Name>>).write(__tmp_frame);  <<=end generate=>> <<=generate for Arrays=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i++) \
		{ \
			_Pragma ("HLS pipeline") \
			__tmp_frame.data = (msg).<<name>>.data[i]; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>>} \
}
<<end generate>>


<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v5_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
		(<<Name>>).read(__tmp_frame); \
		(<<Name>>).read(__tmp_frame); \
	<<=generate for Primitives=>>
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>> = __tmp_frame.data;  <<=end generate=>> <<=generate for Arrays=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i++) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i] = __tmp_frame.data; \
		} \ <<=end generate=>> (<<Name>>).read(__tmp_frame); \
}
<<end generate>>


<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v5_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	__tmp_frame.user = 0; \
	(<<Name>>).write(__tmp_frame); \
	__tmp_frame.user = 1; \
	(<<Name>>).write(__tmp_frame); \
	<<=generate for Primitives=>>
		__tmp_frame.data = (msg).<<name>>; \
		(<<Name>>).write(__tmp_frame);  <<=end generate=>> <<=generate for Arrays=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i++) \
		{ \
			_Pragma ("HLS pipeline") \
			__tmp_frame.data = (msg).<<name>>.data[i]; \
			__tmp_frame.user = 1; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>>__tmp_frame.user = 0;\
		(<<Name>>).write(__tmp_frame); \
}
<<end generate>>


// HWTopics with shifting
#define HWTOPIC_AXIS_DWIDTH 64
#define ARRAY_DWIDTH 8
#define UNROLL_FACTOR HWTOPIC_AXIS_DWIDTH/ARRAY_DWIDTH

<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v6_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	write_section : { \
	__tmp_frame.user = 0; \
	__tmp_frame.last = 0; \
	(<<Name>>).write(__tmp_frame); \
	__tmp_frame.user = 1; \
	(<<Name>>).write(__tmp_frame); \
	<<=generate for Primitives=>>
		__tmp_frame.data = (msg).<<name>>; \
		(<<Name>>).write(__tmp_frame);  <<=end generate=>> <<=generate for Arrays=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=UNROLL_FACTOR) \
		{ \
			_Pragma ("HLS pipeline") \
			__tmp_frame.data = 0; \
			for(int8_t j = UNROLL_FACTOR; j >= 0 ; j--){ \
				_Pragma ("HLS pipeline") \
				__tmp_frame.data = __tmp_frame.data | (0xff & (msg).<<name>>.data[i + j]); \
				if(j > 0){ \
					__tmp_frame.data = __tmp_frame.data << 8; \
				} \
			} \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>>} \
		__tmp_frame.user = 0; \
		__tmp_frame.last = 1; \
		(<<Name>>).write(__tmp_frame); \
}
<<end generate>>


<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v6_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	read_section : { \
	(<<Name>>).read(__tmp_frame); \
	(<<Name>>).read(__tmp_frame); \
	<<=generate for Primitives=>>
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>> = __tmp_frame.data;  <<=end generate=>> <<=generate for Arrays=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=UNROLL_FACTOR) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			for(uint8_t j = 0; j < UNROLL_FACTOR; j++){ \
			_Pragma ("HLS pipeline") \
			(msg).<<name>>.data[i + j] = __tmp_frame.data & 0xff; \
			__tmp_frame.data = __tmp_frame.data >> 8; \
			} \
		} \ <<=end generate=>>	} \
		(<<Name>>).read(__tmp_frame); \
}
<<end generate>>


<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v7_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	write_section : { \
	__tmp_frame.user = 0; \
	__tmp_frame.last = 0; \
	uint64_t tmp_1 = 0; \
	uint64_t tmp_2 = 0; \
	uint64_t tmp_3 = 0; \
	uint64_t tmp_4 = 0; \
	uint64_t tmp_5 = 0; \
	uint64_t tmp_6 = 0; \
	uint64_t tmp_7 = 0; \
	uint64_t tmp_8 = 0; \
	(<<Name>>).write(__tmp_frame); \
	__tmp_frame.user = 1; \
	(<<Name>>).write(__tmp_frame); \
	<<=generate for Primitives=>>
		__tmp_frame.data = (msg).<<name>>; \
		(<<Name>>).write(__tmp_frame);  <<=end generate=>> <<=generate for Arrays_8bit=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=UNROLL_FACTOR) \
		{ \
			_Pragma ("HLS pipeline") \
			tmp_1 = (0xff & ((uint64_t)(msg).<<name>>.data[i])) << 56; \
			tmp_2 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 1])) << 48; \
			tmp_3 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 2])) << 40; \
			tmp_4 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 3])) << 32; \
			tmp_5 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 4])) << 24; \
			tmp_6 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 5])) << 16; \
			tmp_7 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 6])) << 8; \
			tmp_8 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 7])); \
			__tmp_frame.data = tmp_1 | tmp_2 | tmp_3 | tmp_4 | tmp_5 | tmp_6 | tmp_7 | tmp_8; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>>} \
		__tmp_frame.user = 0; \
		__tmp_frame.last = 1; \
		(<<Name>>).write(__tmp_frame); \
}
<<end generate>>


<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v7_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	read_section : { \
	(<<Name>>).read(__tmp_frame); \
	(<<Name>>).read(__tmp_frame); \
	<<=generate for Primitives=>>
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>> = __tmp_frame.data;  <<=end generate=>> <<=generate for Arrays_8bit=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=UNROLL_FACTOR) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i] = (__tmp_frame.data >> 56) & 0xff; \
			(msg).<<name>>.data[i + 1] = (__tmp_frame.data >> 48) & 0xff; \
			(msg).<<name>>.data[i + 2] = (__tmp_frame.data >> 40) & 0xff; \
			(msg).<<name>>.data[i + 3] = (__tmp_frame.data >> 32) & 0xff; \
			(msg).<<name>>.data[i + 4] = (__tmp_frame.data >> 24) & 0xff; \
			(msg).<<name>>.data[i + 5] = (__tmp_frame.data >> 16) & 0xff; \
			(msg).<<name>>.data[i + 6] = (__tmp_frame.data >> 8) & 0xff; \
			(msg).<<name>>.data[i + 7] = (__tmp_frame.data) & 0xff; \
		} \ <<=end generate=>>	} \
		(<<Name>>).read(__tmp_frame); \
}
<<end generate>>



<<generate for HWTOPICSPUB>>
#define ROS_PUBLISH_HWTOPIC_v8_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	write_section : { \
	__tmp_frame.user = 0; \
	__tmp_frame.last = 0; \
	uint64_t tmp_1 = 0; \
	uint64_t tmp_2 = 0; \
	uint64_t tmp_3 = 0; \
	uint64_t tmp_4 = 0; \
	uint64_t tmp_5 = 0; \
	uint64_t tmp_6 = 0; \
	uint64_t tmp_7 = 0; \
	uint64_t tmp_8 = 0; \
	(<<Name>>).write(__tmp_frame); \
	__tmp_frame.user = 1; \
	(<<Name>>).write(__tmp_frame); \
	<<=generate for Primitives=>>
		__tmp_frame.data = (msg).<<name>>; \
		(<<Name>>).write(__tmp_frame);  <<=end generate=>> <<=generate for Arrays_8bit=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			tmp_1 = (0xff & ((uint64_t)(msg).<<name>>.data[i]    )) << 56; \
			tmp_2 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 1])) << 48; \
			tmp_3 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 2])) << 40; \
			tmp_4 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 3])) << 32; \
			tmp_5 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 4])) << 24; \
			tmp_6 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 5])) << 16; \
			tmp_7 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 6])) << 8; \
			tmp_8 = (0xff & ((uint64_t)(msg).<<name>>.data[i + 7])); \
			__tmp_frame.data = tmp_1 | tmp_2 | tmp_3 | tmp_4 | tmp_5 | tmp_6 | tmp_7 | tmp_8; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>> <<=generate for Arrays_16bit=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			tmp_1 = (0xffff & ((uint64_t)(msg).<<name>>.data[i]    )) << 48; \
			tmp_2 = (0xffff & ((uint64_t)(msg).<<name>>.data[i + 1])) << 32; \
			tmp_3 = (0xffff & ((uint64_t)(msg).<<name>>.data[i + 2])) << 16; \
			tmp_4 = (0xffff & ((uint64_t)(msg).<<name>>.data[i + 3])) ; \
			__tmp_frame.data = tmp_1 | tmp_2 | tmp_3 | tmp_4; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>> <<=generate for Arrays_32bit=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			tmp_1 = (0xffffffff & ((uint64_t)(msg).<<name>>.data[i] )) << 32; \
			tmp_2 = (0xffffffff & ((uint64_t)(msg).<<name>>.data[i + 1])); \
			__tmp_frame.data = tmp_1 | tmp_2; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>> <<=generate for Arrays_64bit=>> __tmp_frame.data = (msg).<<name>>.size;  \
		(<<Name>>).write(__tmp_frame); \
		__tmp_frame.data = (msg).<<name>>.capacity; \
		(<<Name>>).write(__tmp_frame); \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			__tmp_frame.data = (msg).<<name>>.data[i]; \
			(<<Name>>).write(__tmp_frame); \
		} \<<=end generate=>>} \
		__tmp_frame.user = 0; \
		__tmp_frame.last = 1; \
		(<<Name>>).write(__tmp_frame); \
}
<<end generate>>


<<generate for HWTOPICSSUB>>
#define ROS_READ_HWTOPIC_v8_timing_<<Name>>( <<Name>>, msg){\
	ap_axis<64,1,1,1> __tmp_frame; \
	read_section : { \
	(<<Name>>).read(__tmp_frame); \
	(<<Name>>).read(__tmp_frame); \
	<<=generate for Primitives=>>
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>> = __tmp_frame.data;  <<=end generate=>> <<=generate for Arrays_8bit=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i] = (__tmp_frame.data >> 56) & 0xff; \
			(msg).<<name>>.data[i + 1] = (__tmp_frame.data >> 48) & 0xff; \
			(msg).<<name>>.data[i + 2] = (__tmp_frame.data >> 40) & 0xff; \
			(msg).<<name>>.data[i + 3] = (__tmp_frame.data >> 32) & 0xff; \
			(msg).<<name>>.data[i + 4] = (__tmp_frame.data >> 24) & 0xff; \
			(msg).<<name>>.data[i + 5] = (__tmp_frame.data >> 16) & 0xff; \
			(msg).<<name>>.data[i + 6] = (__tmp_frame.data >> 8) & 0xff; \
			(msg).<<name>>.data[i + 7] = (__tmp_frame.data) & 0xff; \
		} \ <<=end generate=>> <<=generate for Arrays_16bit=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i]     = (__tmp_frame.data >> 48) & 0xffff; \
			(msg).<<name>>.data[i + 1] = (__tmp_frame.data >> 32) & 0xffff; \
			(msg).<<name>>.data[i + 2] = (__tmp_frame.data >> 16) & 0xffff; \
			(msg).<<name>>.data[i + 3] = (__tmp_frame.data      ) & 0xffff; \
		} \ <<=end generate=>> <<=generate for Arrays_32bit=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i]     = (__tmp_frame.data >> 32) & 0xffffffff; \
			(msg).<<name>>.data[i + 1] = (__tmp_frame.data      ) & 0xffffffff; \
		} \ <<=end generate=>> <<=generate for Arrays_64bit=>> (<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.size = __tmp_frame.data; \
		(<<Name>>).read(__tmp_frame); \
		(msg).<<name>>.capacity = __tmp_frame.data; \
		for (uint32_t i = 0; i < <<num_elems>>; i+=<<unroll_factor>>) \
		{ \
			_Pragma ("HLS pipeline") \
			(<<Name>>).read(__tmp_frame); \
			(msg).<<name>>.data[i] = __tmp_frame.data; \
		} \ <<=end generate=>>	} \
		(<<Name>>).read(__tmp_frame); \
}
<<end generate>>

// ROS Services

#define ROS_SERVICESERVER_SEND_RESPONSE(p_handle,p_handle_msg)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICES_RESPONSE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SERVICESERVER_TRYTAKE(p_handle,p_handle_msg, msg_ptr)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICES_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	msg_ptr = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal), \
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SERVICESERVER_TAKE(p_handle, p_handle_msg )(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICES_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SERVICECLIENT_SEND_REQUEST(p_handle,p_handle_msg)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICEC_REQUEST),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SERVICECLIENT_TRYTAKE(p_handle,p_handle_msg ,msg_ptr)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICEC_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	msg_ptr = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal), \
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_SERVICECLIENT_TAKE(p_handle, p_handle_msg )(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_SERVICEC_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))




//ROS Actions

#define ROS_ACTION_SERVER_GOAL_REJECT       0
#define ROS_ACTION_SERVER_GOAL_ACCEPT       1


#define ROS_ACTIONSERVER_GOAL_TAKE(p_handle, p_handle_msg)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_GOAL_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_GOAL_TRYTAKE(p_handle,p_handle_msg, msg_ptr)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_GOAL_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	msg_ptr = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal), \
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))


#define ROS_ACTIONSERVER_GOAL_DECIDE(p_handle,accept)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_GOAL_DECIDE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, accept),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_RESULT_TAKE(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_RESULT_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_RESULT_TRYTAKE(p_handle, msg_ptr)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_RESULT_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	msg_ptr = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal), \
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_RESULT_SEND(p_handle, p_handle_msg )( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_RESULT_SEND),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_FEEDBACK(p_handle, p_handle_msg )( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_FEEDBACK),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_CANCEL_TAKE(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_CANCEL_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_CANCEL_TRYTAKE(p_handle)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_CANCEL_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONSERVER_CANCEL_SEND(p_handle)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONS_CANCEL_SEND),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTION_CLIENT_GOAL_REJECTED       0
#define ROS_ACTION_CLIENT_GOAL_ACCEPTED       1


#define ROS_ACTIONCLIENT_GOAL_SEND(p_handle, p_handle_msg)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_GOAL_SEND),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_GOAL_TRYTAKE(p_handle,accept)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_GOAL_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	accept = stream_read(osif_sw2hw, osif_hw2sw, hwt_signal),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_GOAL_TAKE(p_handle,accept)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_GOAL_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	accept = stream_read(osif_sw2hw,osif_hw2sw, hwt_signal),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal)) 

#define ROS_ACTIONCLIENT_RESULT_SEND(p_handle)(\
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_RESULT_SEND),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_RESULT_TRYTAKE(p_handle, p_handle_msg)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_RESULT_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_RESULT_TAKE(p_handle, p_handle_msg )( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_RESULT_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_FEEDBACK_TAKE(p_handle, p_handle_msg )( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_FEEDBACK_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_FEEDBACK_TRYTAKE(p_handle, p_handle_msg )( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_FEEDBACK_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_write(osif_hw2sw, p_handle_msg),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))


#define ROS_ACTIONCLIENT_CANCEL_SEND(p_handle)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_CANCEL_SEND),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_CANCEL_TRYTAKE(p_handle)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_CANCEL_TRYTAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

#define ROS_ACTIONCLIENT_CANCEL_TAKE(p_handle)( \
	stream_write(osif_hw2sw, OSIF_CMD_ROS_ACTIONC_CANCEL_TAKE),\
	stream_write(osif_hw2sw, p_handle),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal)) 

/*
 * Gets the pointer to the initialization data of the ReconOS thread
 * specified by reconos_hwt_setinitdata.
 */
#define GET_INIT_DATA()(\
	stream_write(osif_hw2sw, OSIF_CMD_THREAD_GET_INIT_DATA),\
	stream_read(osif_sw2hw,osif_hw2sw, hwt_signal))

/*
 * Reads several words from the main memory into the local ram. Therefore,
 * divides a large request into smaller ones of length at most
 * MEMIF_CHUNK_BYTES and splits request at page borders to guarantee
 * correct address translation.
 *
 *   src - start address to read from the main memory
 *   dst - array to write data into
 *   len - number of bytes to transmit (bytes)
 *   
 */
#define MEM_READ(src,dst,len){\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (src), __i = 0;\
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_READ | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
		_Pragma ("HLS pipeline")  \
			(dst)[__i++] = memif_mem2hwt.read();\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
		}\
	}}
/*
* Can read byte-wise from int8/uint8 and write to int8/uint8
*/
#define MEM_READ_INT8(src,dst,len){\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (src), __i = 0;\
	uint64_t __tmp = 0;\
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_READ | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
		_Pragma ("HLS pipeline")  \
			__tmp = memif_mem2hwt.read();\
            for(uint8_t __k = 0; __k < 8; __k++ ) { \
                (dst)[__i++] = __tmp & 0xff;\
                __tmp = __tmp >> 8;}\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
			__tmp = 0;\
		}\
	}}

/*
 * Writes several words from the local ram into main memory. Therefore,
 * divides a large request into smaller ones of length at most
 * MEMIF_CHUNK_BYTES and splits request at page borders to guarantee
 * correct address translation.
 *
 *   src - array to read data from
 *   dst - start address to read from the main memory
 *   len - number of bytes to transmit (bytes)
 */
#define MEM_WRITE(src,dst,len){\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (dst), __i = 0;\
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_WRITE | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
		_Pragma ("HLS pipeline")  \
			memif_hwt2mem.write((src)[__i++]);\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
		}\
	}}


/*
* Can read byte-wise from memory (int8/uint8) and write to local ram (int8/uint8)
*/
#define MEM_WRITE_INT8_REVERSED(src,dst,len){\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (dst), __i = 0;\
	uint64_t __temp; \
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_WRITE | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
			__temp = 0;\
			for(uint8_t __k = 0; __k < 8; __k++){\
				__temp = __temp | (0xff & (src)[__i + __k]);\
				if(__k < 7){\
				__temp = __temp << 8;}\
			}\
		_Pragma ("HLS pipeline")  \
			memif_hwt2mem.write(__temp);\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
			__i += 8;\
		}\
	}}

#define MEM_WRITE_INT8(src,dst,len){\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (dst), __i = 0;\
	uint64_t __temp; \
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_WRITE | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
			__temp = 0;\
			for(int8_t __k = 7; __k >= 0; __k--){\
				__temp = __temp | (0xff & (src)[__i + __k]);\
				if(__k > 0){\
				__temp = __temp << 8;}\
			}\
		_Pragma ("HLS pipeline")  \
			memif_hwt2mem.write(__temp);\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
			__i += 8;\
		}\
	}}

/*
 * Writes several words from the local ram into main memory. Therefore,
 * divides a large request into smaller ones of length at most
 * MEMIF_CHUNK_BYTES and splits request at page borders to guarantee
 * correct address translation.
 *
 *   src - array to read data from
 *   dst - start address to read from the main memory
 *   len - number of bytes to transmit (bytes)
 */


#define MEM_READ_TO_STREAM( src, dst, len){ \
	RRUBASETYPE __len, __rem; \
	RRUBASETYPE __addr = (src), __i = 0; \
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_READ | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
		_Pragma ("HLS pipeline")  \
			dst.write(memif_mem2hwt.read());\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
		}\
	}\
}

#define MEM_WRITE_FROM_STREAM( src, dst, len)\
{\
	RRUBASETYPE __len, __rem;\
	RRUBASETYPE __addr = (dst), __i = 0;\
	for (__rem = (len); __rem > 0;) {\
		RRUBASETYPE __to_border = MEMIF_CHUNK_BYTES - (__addr & MEMIF_CHUNK_MASK);\
		RRUBASETYPE __to_rem = __rem;\
		if (__to_rem < __to_border)\
			__len = __to_rem;\
		else\
			__len = __to_border;\
		\
		stream_write(memif_hwt2mem, MEMIF_CMD_WRITE | __len);\
		stream_write(memif_hwt2mem, __addr);\
		\
		for (; __len > 0; __len -= RRBASETYPEBYTES) {\
		_Pragma ("HLS pipeline")  \
			RRUBASETYPE tmp = src.read();\
			memif_hwt2mem.write(tmp);\
			__addr += RRBASETYPEBYTES;\
			__rem -= RRBASETYPEBYTES;\
		}\
	}\
}

/*
 * Terminates the current ReconOS thread.
 */
#define THREAD_EXIT(){\
	stream_write(osif_hw2sw, OSIF_CMD_THREAD_EXIT);\
	while(1);}

#endif /* RECONOS_CALLS_H */
