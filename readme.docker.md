# Docker

## Rationale

Practice, practice =) Also it removes the need for local installations of Node and related libraries. Database setup
is also easy using docker.

# Development

Launch the compose file with:
```bash
docker compose up
```

This builds image for the backend, downloads MySQL image and launches containers for them. Bind mount is created for
the source directory, and a volume is created for node_modules directory. The backend REST API is being exposed
in the port 3000.

