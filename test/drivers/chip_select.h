/**
 * \file chip_select.h
 *
 * This file is used to define a chip select initialization function
 */
#ifndef CHIP_SELECT_H
#define CHIP_SELECT_H

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     *\brief Should be called in each driver test setUp()
     * 
     */
    void chip_select_init(void);
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* CHIP_SELECT_H */