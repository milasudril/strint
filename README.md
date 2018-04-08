# Strint

Header-only library for providing stricter integer types. Features:

 * An integer can always be promoted to a larger type
 * If the integer is goinging to be downcasted, a CastException is thrown when the target type cannot store the source
   value. You may wish to repackage it and rethrow in order to provide better error messages.
 * Aliases for common integer sizes are provided in `common_types.hpp`
 * The library has some helper types for portable serialization `Integer<...>::typeId()` and `Integer::typeName()`. For
   platform dependent types, these map to the id of the integer type with exact size, that has the same size that the
   platform dependent type. For example, on 64-bit Linux systems, `Long` maps to `i64`, but on Windows platforms, `Long`
   maps to `i32`
