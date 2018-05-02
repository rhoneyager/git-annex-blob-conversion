# git-annex-blob-conversion

## Synopsis

This is a filter, used in reposurgeon, that will filter out large blobs from the repository.
These blobs will instead be stored in an external cache directory.
This is useful for converting a repository to use git-annex, as the usual git-filter-branch
process is _very_ slow when converting large repositories.

This program uses C++17. May require the FIlesystem TS in the future.

## Usage

```
git-annex-blob-conversion {threshold_size} {large_blob_storage_dir} {large_blob_public_url} [filenames...]
```

Parameters:

- threshold_size: The minimum size of the blob, in bytes, for the file to be filtered.
- large_blob_storage_dir: Location where the exported blobs are written to.
- large_blob_public_url: Location where you will expect to find the blobs (as a url, like ```file://```)
- filenames: A space-separated list of all of the locations in the repository that reference the blob. 
  Optional. Can be used for filtering files based on extension.

Requirements:
- large_blob_storage_dir must exist and be a writable directory.

### Usage with reposurgeon

TODO

## License

This is explicitly released to the public domain. See the [LICENSE](./LICENSE) file.

