# README for QDPXX_EX

This program is an extension of the **`QDP++`** [https://github.com/usqcd-software/qdpxx.git]

It would support :
- to Write/Read datafile, such as LatticePropagator, GaugeFile......
  > **`QDPIO_SERIAL`/`QDPIO_PARALLEL`** 
  ```C++
  //! File access mode
  enum QDP_serialparallel_t
  {
    QDPIO_SERIAL,
    QDPIO_PARALLEL
  };
  ```
  > **QDP_volfmt_t : `QDPIO_SINGLEFILE`/`QDPIO_MULTIFILE`**,
  when Reading, this param does not need. QIO would autodetect. 
  ```C++
  //! File format
  enum QDP_volfmt_t
  {
        QDPIO_SINGLEFILE,
        QDPIO_MULTIFILE,
        QDPIO_PARTFILE
  };
  ```
- 