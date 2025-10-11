<h1 align="center">💡<strong> Declarations</strong></h1>
<p align="center">
  <a href="#writing_hand-declaration-syntax">Declaration Syntax</a> •
  <a href="#file_cabinet-storage-classes">Storage Classes</a> •
  <a href="#bookmark-type-qualifiers">Type Qualifiers</a> •
  <a href="#pencil2-declarators">Declarators</a> •
  <a href="#seedling-initializers">Initializers</a> •
  <a href="#zap-inline-functions">Inline Functions</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :writing_hand: Declaration Syntax

* Declarations in C are used to explain the meaning of identifiers to the compiler.
* A declaration in C has the following general form: ```declaration_specifiers declarators```.
   * ```declaration_specifiers``` provide information about the properties of the identifiers being declared.
   * ```declarators``` provide the names of the identifiers being declared. They may provide additional information about some of their properties as well.
   * C89 recognizes three categories of declaration specifiers.
      * ```Storage classes```.
         * C has four storage classes: ```auto```, ```static```, ```extern``` and ```register```.
         * A declaration cannot have more than one storage class.
         * A declaration may have no storage class at all.
         * Storage classes must always be mentioned before anything else in a declaration. This is one of very few rules C enforces on the order of declaration specifiers.
      * ```Type qualifiers```.
         * C89 has two type qualifiers only: ```const``` and ```volatile```.
         * C99 adds a third type qualifier: ```restrict```.
         * A declaration can have multiple different type qualifiers.
         * A declaration may have no type qualifiers at all.
      * ```Type specifiers```.
         * C's type specifiers come in multiple forms.
         * Keywords like ```void```, ```char```, ```short```, ```int```, ```long```, ```float```, ```double```, ```signed``` and ```unsigned``` are all type specifiers.
            * These keywords can be combined (some combinations are invalid).
            * When combined, the order in which these keywords appear is irrelevant.
         * Structure, union and enumeration specifications are also type specifiers.
         * Custom types created using ```typedef``` are type specifiers as well.
   * C99 adds a fourth declaration specifier category.
      * ```Function specifiers```.
         * This category includes a single keyword: ```inline```.
         * ```inline``` can only be used with function declarations, hence the name of the category.
   * Type specifiers' and type qualifiers' relative positions in a declaration are interchangeable as long as they come after the storage class.
   * Declarators have several rules:
      * They come in different forms.
         * Identifiers like the names of simple variables.
         * Identifiers followed by ```[]```. These identifiers are names of arrays.
         * Identifiers preceded by ```*```. These identifiers are names of pointer variables.
         * Identifiers followed by ```()```. These identifiers are names of functions.
      * Several declarators can be grouped together and associated to a single set of declaration specifiers. In this case, these declarators are separated by commas.
      * A declarator that represents a variable may be followed by an initializer.

## :file_cabinet: Storage Classes

## :bookmark: Type Qualifiers

## :pencil2: Declarators

## :seedling: Initializers

## :zap: Inline Functions

## :game_die: Miscellaneous