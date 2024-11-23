file(GLOB MESSAGE_SRC_LIST
    "*.cpp"
)

target_sources(main PRIVATE ${MESSAGE_SRC_LIST})
