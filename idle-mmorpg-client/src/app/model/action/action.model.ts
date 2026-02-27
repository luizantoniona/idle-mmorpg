export type ActionOption = {
    stage: number;
    duration: number;
    experience: number;
    skill: number;
    item?: string;
};

export type Action = {
    type: number;
    description: string;
    options?: ActionOption[];
    selectedOption?: ActionOption;
};