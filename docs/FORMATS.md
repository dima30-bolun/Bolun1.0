# Luna formats

`.ben` files start with `BEN1`, followed by length-prefixed application name, entry point, payload size and payload bytes. Luna Runtime validates the header and executes the payload through the Luna runtime API.

`.bapp` manifests use readable key-value records for id, name, executable, signature and localized names. Package contents are stored beside the manifest in icons, resources and locale folders.

`.luna` project files use readable key-value records for name, version and source entries so SDK tools can build reproducible application packages.
