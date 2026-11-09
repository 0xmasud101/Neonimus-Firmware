# modules/mcp_bridge/ - Phase 4 (not started)

PC-side bridge (serial or WiFi transport) so an MCP-compatible LLM
client on your computer can trigger scans on the device and read back
summarized results. The device-side half lives here; the PC-side MCP
server itself will likely be a small separate Python/Node project, not
firmware - note that split once design starts.

Scope reminder: this bridge should only ever expose actions that are
valid for hardware the operator owns or is authorized to test, and
summarized/aggregated results - not raw packet capture exfiltrated to
an arbitrary remote LLM endpoint. Keep that boundary in the design doc
before writing the transport code.

Will be gated behind `NEONIMUS_HAS_MCP_BRIDGE` (see
`branding/neonimus_config.h`).
