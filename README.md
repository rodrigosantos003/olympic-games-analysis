# ATAD 23/24 - Project
## Respository
Link: https://github.com/estsetubal-atad-2023-24-projetos/projeto-en-assignment-pm_202100722

Authors:
- João Fernandes - 202100718
- Rodrigo Santos - 202100722
- Rúben Dâmaso - 202100723

Teacher: Patrícia Macedo [Class 1ºL_EI-08]


## Compiling and executing

```console
$> make
```

```console
$> ./prog
```

## Using valgrind

*Valgrind* is very useful to detect "memory leaks" if your program uses *dynamic memory allocation*. You must compile the program with *debug* symbols and then run the executable through `valgrind`:

```console
$> make debug
$> valgrind --leak-check=full ./prog 
```

Alternatively, you can use the *bash script* already included:

```console
$> make debug
$> bash mem_check.sh
```

**When the program exits** it will present you with memory leak information.

## Debugging

In the **Run** tab (left side) you should see a green play icon ▶️ at the top beside "gdb - Debug project". Click on it and the debug will start. Do not forget to set your *breakpoints*.

## Generating documentation

You'll need `doxygen` installed and follow the doxygen documentation format. A `Doxyfile` is already provided that is suited for the C language. Use:

```bash
$> doxygen Doxyfile
```

and you'll end up with a `html` folder containing the generated documentation.